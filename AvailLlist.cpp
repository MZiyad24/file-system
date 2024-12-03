struct AvailableNode {
    int position; 
    AvailableNode* next; 

    AvailableNode(int pos) : position(pos), next(nullptr) {}
};

class AvailList {
private:
    AvailableNode* head; 

public:
    AvailList() : head(nullptr) {}

    ~AvailList() {
        while (head) {
            AvailableNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(int position) {
        AvailableNode* newNode = new AvailableNode(position);
        newNode->next = head;
        head = newNode;
    }

    int get() {
        if (!head) return -1; 
        int position = head->position;
        AvailableNode* temp = head;
        head = head->next;
        delete temp;
        return position;
    }

    void print() {
        AvailableNode* temp = head;
        cout << "AVAIL LIST: ";
        while (temp) {
            cout << temp->position << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};
