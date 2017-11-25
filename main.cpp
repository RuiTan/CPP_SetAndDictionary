#include "LinkedSet.h"

int main() {
    LinkedSet<int> linkedSet;
    cout << linkedSet;
    linkedSet.addMember(1);
    cout << linkedSet;
    linkedSet.addMember(3);
    cout << linkedSet;
    linkedSet.addMember(2);
    linkedSet.addMember(6);
    linkedSet.addMember(4);
    linkedSet.addMember(4);
    linkedSet.addMember(5);
    cout << linkedSet;
    linkedSet.delMember(2);
    cout << linkedSet;
    SetNode<int> *node = linkedSet.getMember(4);
    if (node) cout << node->data << endl;
    linkedSet.makeEmpty();
    cout << linkedSet;
    vector<int> a = {1,5,9};
    linkedSet.addMember(a);
    cout << linkedSet;
    vector<int> b = {7, 3, 4};
    linkedSet.addMember(b);
    cout << linkedSet << endl;
    cout << linkedSet;

    LinkedSet<int> linkedSet1;//实际上调用的是构造函数而非赋值操作
    linkedSet1 = linkedSet;
    cout << linkedSet1 << endl;
    if (linkedSet == linkedSet1){
        cout << "true";
    }else {
        cout << "false";
    }

    LinkedSet<int> linkedSet2;
    vector<int> c = {12, 1, 5, 54, 90};
    linkedSet2.addMember(c);
    LinkedSet<int> linkedSet3;
    linkedSet3 = linkedSet * linkedSet2;
    cout << linkedSet3;
    linkedSet3 = linkedSet + linkedSet2;
    cout << linkedSet3;
    cout << linkedSet3.getLast()->data;
    linkedSet3 = linkedSet - linkedSet2;
    cout << linkedSet3;

    vector<string> d = {"tanrui", "liyang", "xiaoxin", "chenchao"};
    vector<string> e = {"zhaoyun", "alen"};
    LinkedSet<string> linkedSet4;
    linkedSet4.addMember(d);
    LinkedSet<string> linkedSet5;
    linkedSet5.addMember(e);
    LinkedSet<string> linkedSet6;
    linkedSet6 = linkedSet4 + linkedSet5;
    cout << linkedSet6;
    cout << linkedSet6.getLast()->data;
    cout << linkedSet4;
    cout << linkedSet4.getLast()->data;
    linkedSet4.delMember("xiaoxin");
    cout << linkedSet4;
    cout << linkedSet4.getLast()->data;
    cout << linkedSet6.Max() << linkedSet6.Min() << endl;

    cout << linkedSet6.subSet(linkedSet4);
    cout << linkedSet4.subSet(linkedSet6);
    cout << linkedSet6.subSet(linkedSet5);

    return 0;
}