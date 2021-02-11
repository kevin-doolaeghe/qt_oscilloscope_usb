#include "decoder.h"

Decoder::Decoder()
{

}

QList<QString> Decoder::decode(QString frame, char sep)
{
    return frame.split(sep);
}

QString Decoder::getDataFromIndex(QList<QString> data, int index)
{
    QString res;

    if (data.length() > index) res = data.at(index);
    return res;
}
