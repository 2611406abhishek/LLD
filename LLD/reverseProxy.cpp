#include <bits/stdc++.h>
using namespace std;

class Server
{

public:
    bool isUp;

    Server()
    {
        isUp = true;
    }
    void updateStatus(bool status)
    {
        isUp = status;
    }
};

class ServerQueue
{

public:
    queue<int> servers;

    SeverQueue()
    {
    }
    ServerQueue(const vector<int> &serverList)
    {
        for (int i = 0; i < serverList.size(); i++)
        {
            servers.push(i);
        }
    }

    int getNextServer()
    {
        if (servers.size() == 0)
            return -1;
        int nextServer = servers.front();
        servers.pop();
        servers.push(nextServer);
        return nextServer;
    }

    void removeServer(int serverIndex)
    {
        queue<int> newQueue;
        while (servers.size())
        {
            int front = servers.front();
            servers.pop();
            if (front != serverIndex)
            {
                newQueue.push(front);
            }
        }
        servers = newQueue;
    }

    void addServer(int serverIndex)
    {
        servers.push(serverIndex);
    }
};

class LoadBalancer
{
public:
    unordered_map<int, Server> servers;
    unordered_map<int, ServerQueue> serverQueues;

    LoadBalancer() {}
    LoadBalancer(const vector<int> &serverIPs, const vector<int> &endpoints)
    {

        for (auto ip : serverIPs)
        {
            servers[ip] = Server();
        }

        for (auto endpoint : endpoints)
        {

            serverQueues[endpoint] = ServerQueue(serverIPs);
        }
    }

    void handleRequest(int endpoint, int req)
    {
        int requestedServer = serverQueues[endpoint].getNextServer();
        if (requestedServer == -1)
        {
            cout << "Sorry NO server is available to handle request" << endl;
            return;
        }
        cout << "Handling request ::" << req << " for endpoint " << requestedServer << endl;
    }

    void handleSpecialHit(int serverIP, bool status)
    {
        servers[serverIP].updateStatus(status);
        if (status == false)
        {
            for (auto &serverQueue : serverQueues)
            {
                serverQueue.second.removeServer(serverIP);
            }
        }
        else
        {
            for (auto &serverQueue : serverQueues)
            {
                serverQueue.second.addServer(serverIP);
            }
        }
    }
};

int main()
{
    vector<int> serverIPs = {1, 2, 3, 4};
    vector<int> endpoints = {101, 102};

    LoadBalancer LoadBalancer(serverIPs, endpoints);

    LoadBalancer.handleRequest(101, 1);
    LoadBalancer.handleRequest(102, 2);

    LoadBalancer.handleSpecialHit(1, false);

    LoadBalancer.handleRequest(101, 3);
    return 0;
}
