#ifndef PARSERTHREAD_H
#define PARSERTHREAD_H

#include <QThread>

class parserthread : public QThread
{
    Q_OBJECT
public:
    explicit parserthread(QObject *parent = 0);
    int rd3302;
    QString filename;
    QString calFileName;
    bool calMode;
    bool noRawMode;
    void parse();

signals:
    void completion(double percentfinished);
    void finished();

protected:
    void run();
    //QMutex mutex;
    //QWaitCondition condition;
    //bool restart;


};

#endif // PARSERTHREAD_H
