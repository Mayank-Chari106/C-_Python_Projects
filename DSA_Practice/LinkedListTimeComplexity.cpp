#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;
    int size;

public:
    SinglyLinkedList() {
        head = nullptr;
        size = 0;
    }

    void insertAtBeginning(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void insertAtEnd(int data) {
        Node* newNode = new Node(data);

        if(head == nullptr) {
            head = newNode;
            size++;
            return;
        }

        Node* current = head;
        while(current->next != nullptr)
            current = current->next;

        current->next = newNode;
        size++;
    }

    void insertAtPosition(int data, int position) {
        if(position < 0 || position > size)
            return;

        if(position == 0) {
            insertAtBeginning(data);
            return;
        }

        Node* newNode = new Node(data);
        Node* current = head;

        for(int i=0;i<position-1;i++)
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
        size++;
    }

    bool deleteNode(int data) {
        if(head == nullptr)
            return false;

        if(head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        Node* current = head;

        while(current->next != nullptr) {
            if(current->next->data == data) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                size--;
                return true;
            }
            current = current->next;
        }

        return false;
    }
};

int main() {

    int N[3];

    cout << "Enter three values of N: ";
    cin >> N[0] >> N[1] >> N[2];

    cout << "\n-------------------------------------------------------------\n";
    cout << "N\tInsertBegin\tInsertEnd\tInsertPos\tDelete\n";
    cout << "-------------------------------------------------------------\n";

    for(int k=0;k<3;k++) {

        int n = N[k];
        SinglyLinkedList list;

        auto start = high_resolution_clock::now();
        for(int i=0;i<n;i++)
            list.insertAtBeginning(i);
        auto stop = high_resolution_clock::now();
        auto t1 = duration_cast<microseconds>(stop-start).count();

        start = high_resolution_clock::now();
        for(int i=0;i<n;i++)
            list.insertAtEnd(i);
        stop = high_resolution_clock::now();
        auto t2 = duration_cast<microseconds>(stop-start).count();

        start = high_resolution_clock::now();
        for(int i=0;i<n;i++)
            list.insertAtPosition(i, i/2);
        stop = high_resolution_clock::now();
        auto t3 = duration_cast<microseconds>(stop-start).count();

        start = high_resolution_clock::now();
        for(int i=0;i<n;i++)
            list.deleteNode(i);
        stop = high_resolution_clock::now();
        auto t4 = duration_cast<microseconds>(stop-start).count();

        cout << n << "\t"
             << t1 << "\t\t"
             << t2 << "\t\t"
             << t3 << "\t\t"
             << t4 << endl;
    }

    cout << "-------------------------------------------------------------\n";
system("pause");
    return 0;
}