#include "foodbock.h"
#include "config.h"

static const qreal FOOD_RADIUS = 3.0;

Food::Food(qreal x, qreal y)
{
    setPos(x, y);
    setData(GD_Type, GO_Food);
}

QRectF Food::boundingRect() const{
    return QRect(-TILE_SIZE, -TILE_SIZE, TILE_SIZE*2, TILE_SIZE*2);
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), Qt::red);

    painter->restore();
}

QPainterPath Food::shape() const {
    QPainterPath p;
    p.addEllipse(QPointF(TILE_SIZE/2, TILE_SIZE/2), FOOD_RADIUS, FOOD_RADIUS);
    return p;
}
