#ifndef DECODER_H
#define DECODER_H

#include <QList>
#include <QString>

class Decoder
{
public:
    Decoder();
    static QList<QString> decode(QString frame, char sep = ' ');
    static QString getDataFromIndex(QList<QString> data, int index);
};

#endif // DECODER_H
