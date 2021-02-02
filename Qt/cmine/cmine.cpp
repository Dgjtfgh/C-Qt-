#include "cmine.h"

#include <QDebug>
#include <QMouseEvent>
#include <QDebug>

Cmine::Cmine(QWidget *parent,int row,int col,int num_mine,int d) : QWidget(parent),
    row(row),
    col(col),
    d(d),
    num_mine(num_mine)
{
    draw_mousemove=false;
    gameover=false;
    hqcount=num_mine;
    count=row*col-num_mine;
    offset=0.5;
    int size=row*col;
    //num_mine=10;
    board.fill(QVector<char>(col,'0'),row);  // 初始化二维数组 都为'0'
    _board.fill(QVector<char>(col,'0'),row);
    //_board[0][2]='f';

    QHash<int, int> hash;
    while(hash.size() <= 10) {
        int randint=rand()%size; // 产生一个0~size的随机数
        QHash<int, int>::const_iterator i = hash.find(randint);
        if(i != hash.end()) {
            continue;
        }
        int _row=randint/col;    // 行
        int _col=randint%col;    // 列
        board[_row][_col]='m';   // 随机埋雷
        hash.insert(randint, randint);
//        qDebug()<<("(") << _row << (",") << _col <<( ")");

    }
//    for(int i=0;i<num_mine;i++)
//    {
//        int randint=rand()%size; // 产生一个0~size的随机数
//        int _row=randint/col;    // 行
//        int _col=randint%col;    // 列
//        board[_row][_col]='m';   // 随机埋雷
//        printf("(%d,%d)",&_row, &_col);
//        qDebug()<<("(") << _row << (",") << _col <<( ")");
//    }
    calculateMineAround();       // 计算非雷位置周围的雷数
    this->setFixedSize(col*d,row*d);  // 设置窗口大小
    this->setWindowFlag(Qt::FramelessWindowHint); // 设置窗口标志  为无边界且用户无法移动的窗口
    setMouseTracking(true); // 开启实时监控鼠标移动

}

void Cmine::calculateMineAround()
{
    for(int i=0;i<row;i++)  // 遍历行
    {
        for(int j=0;j<col;j++)  // 遍历列
        {
            if(board[i][j]=='0') // 跳过雷
            {
                int count=0;  // 计数 周围八个位置的雷数
                if(j+1<col&&board[i][j+1]=='m') // 存在右伙伴且是雷
                {
                    count++;
                }
                if(j-1>=0&&board[i][j-1]=='m') // 存在左伙伴且是雷
                {
                    count++;
                }
                for(int k=-1;k<=1;k++)
                {
                    if(i-1>=0&&j+k>=0&&j+k<col&&board[i-1][j+k]=='m') // 上方位三个伙伴
                    {
                        count++;
                    }
                    if(i+1<row&&j+k>=0&&j+k<col&&board[i+1][j+k]=='m')// 下方位三个伙伴
                    {
                        count++;
                    }
                }
                board[i][j]='0'+count; // 赋值
            }

        }
    }
}

void Cmine::paintEvent(QPaintEvent *)
{
    painter=new QPainter;

    draw_Board();

    if(draw_mousemove)
    {
        //qDebug()<<"mousemove";
        draw_Mousemove(mousemove_row,mousemove_col);
        draw_mousemove=false;
    }
}

void Cmine::mouseMoveEvent(QMouseEvent *event)
{
    double x=event->x();
    double y=event->y();
    mousemove_row=y/d;
    mousemove_col=x/d;
    draw_mousemove=true;
    update();
}

void Cmine::mousePressEvent(QMouseEvent *event)
{
    if(gameover == true){
        return;
    }

    double x=event->x();
    double y=event->y();
    int mousepress_row=y/d;
    int mousepress_col=x/d;
    if (_board[mousepress_row][mousepress_col]=='o'){
        return;
    }
    if(event->button()==Qt::LeftButton)
    {
        if(_board[mousepress_row][mousepress_col]=='f') {
            hqcount++;
            emit changehqcount();
        }
        _board[mousepress_row][mousepress_col]='o';
        if(board[mousepress_row][mousepress_col]=='m')
        {
            gameover=true;
            emit sig_lost();
        }
        else
        {
            count--;
            emit sig_count();
        }

    }
    if(event->button()==Qt::RightButton)
    {
        if(_board[mousepress_row][mousepress_col]=='0')
        {
            //qDebug()<<"?";
            if (hqcount <= 0){
                _board[mousepress_row][mousepress_col]='?';
            } else {
                _board[mousepress_row][mousepress_col]='f';
                hqcount--;
                emit changehqcount();
            }

        } else if(_board[mousepress_row][mousepress_col]=='f')
        {
            //qDebug()<<"f";
            if(hqcount < num_mine){
                hqcount++;
                emit changehqcount();
                emit sig_count();
            }
            _board[mousepress_row][mousepress_col]='?';
        }
        else if(_board[mousepress_row][mousepress_col]=='?')
        {
            _board[mousepress_row][mousepress_col]='0';
        }

    }

    update();
}

void Cmine::draw_Board()
{

    painter->begin(this);
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            //qDebug()<<_board[i][j];
            switch (_board[i][j])
            {
            case '0':
                //qDebug()<<"0";
                draw_None(i,j);
                break;
            case '?':
                //qDebug()<<"?";
                //if(board[i][j])
                draw_Ques(i,j);
                break;
            case 'f':
                //qDebug()<<"ff";
                draw_Flag(i,j);
                break;
            case 'o':
                //qDebug()<<"o";
                draw_Open(i,j);
                break;
            default:
                //qDebug()<<"draw";
                break;
            }
        }
    }
    painter->end();
}



void Cmine::draw_None(int _row, int _col)
{
    painter->setBrush(Qt::gray);
    painter->drawRect(_col*d+offset,_row*d+offset,d-offset*2,d-offset*2);
    painter->setBrush(Qt::NoBrush);
}

void Cmine::draw_Ques(int _row, int _col)
{
    draw_None(_row,_col);
    QPen pen=painter->pen();
    painter->setPen(QPen(Qt::red));
    QFont font=painter->font();
    QFont font1=font;
    font.setPointSize(12);

    painter->setFont(font);
    painter->drawText(_col*d,_row*d,d,d,5,"?");
    painter->setPen(pen);
    painter->setFont(font1);
}

void Cmine::draw_Flag(int _row, int _col)
{
    draw_None(_row,_col);

    QImage _image(":/icons/flag1.png");
    _image=_image.scaled(d,d);
    //qDebug()<<_image.depth();
    auto data=_image.bits();
    QImage image(data,d,d,QImage::Format_ARGB32);
    //qDebug()<<image.depth();
    image=getTransparentImage(image,QPoint(1,1));
    //qDebug()<<image.pixelColor(1,1);
    //qDebug()<<image.size();
    painter->drawImage(_col*d,_row*d,image);
}

void Cmine::draw_Open(int _row, int _col)
{
    if(board[_row][_col]=='m')
    {
        QImage image(":/icons/mine1.png");
        image=image.scaled(d-offset*2,d-offset*2);
        painter->drawRect(_col*d+offset*0.5,_row*d+offset*0.5,d-offset,d-offset);

        painter->drawImage(_col*d+offset+3,_row*d+offset,image);

        _board.fill(QVector<char>(col,'o'),row);
    }
    else
    {
        painter->drawRect(_col*d+offset,_row*d+offset,d-offset*2,d-offset*2);

        QPen pen=painter->pen();
        painter->setPen(QPen(Qt::blue));
        QFont font=painter->font();
        QFont font1=font;
        font.setPointSize(15);

        painter->setFont(font);
        painter->drawText(_col*d,_row*d,d,d,5,QString(board[_row][_col]));
        painter->setPen(pen);
        painter->setFont(font1);


    }
}

void Cmine::draw_Mousemove(int _row, int _col)
{
    painter->begin(this);
    painter->setBrush(QBrush(QColor(255,255,255,150)));
    painter->drawRect(_col*d-offset,_row*d-offset,d-offset*2,d-offset*2);

    painter->setBrush(Qt::NoBrush);
    painter->end();
}

QImage Cmine::getTransparentImage(QImage image, QPoint point)
{
    if(image.valid(point))
    {
        QRgb rgb=image.pixel(point);

        for(int i=0; i<image.width();i++)
        {
            for(int j=0;j<image.height();j++)
            {
                if(rgb==image.pixel(i,j))
                {
                    QColor rgba = QColor(0, 1, 1, 1);
                    //qDebug()<<i<<j;
                    image.setPixelColor(i,j,rgba);
                }
            }
        }
    }
    return image;
}
