#include "chatserver.h"

ChatServer::ChatServer(QObject *parent)
    : QTcpServer{parent}
{

}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    // This method will get called every time a client tries to connect.
    // We create an object that will take care of the communication with this client
    ServerWorker *worker = new ServerWorker(this);
    // we attempt to bind the worker to the client
    if (!worker->setSocketDescriptor(socketDescriptor)) {
        // if we fail we clean up
        worker->deleteLater();
        return;
    }
    // connect the signals coming from the object that will take care of the
    // communication with this client to the slots in the central server
    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));
    connect(worker, &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));
    connect(worker, &ServerWorker::jsonReceived, this, std::bind(&ChatServer::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);
    // we append the new worker to a list of all the objects that communicate to a single client
    m_clients.append(worker);
    // we log the event
    emit logMessage(QStringLiteral("New client Connected"));
}

void ChatServer::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination); // make sure destination is not null
    destination->sendJson(message); // call directly the worker method
}

void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    // iterate over all the workers that interact with the clients
    for (ServerWorker *worker : m_clients) {
        if (worker == exclude)
            continue; // skip the worker that should be excluded
        sendJson(worker, message); //send the message to the worker
    }
}
