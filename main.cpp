#include "MyBag.h"
int main(){
    int t;
    cin >> t;
    T x;
    MyBag b;
    while(t){
        switch (t)
        {
        case 1:
            cin >> x;
            if (b.contains(x))
                cout << "OK" << endl;
            else
                cout << "OBS" << endl;
            break;

        case 2:
            cin >> x;
            b.insert(x);
            break;
        
        case 3:
            cin >> x;
            b.erase(x);
            break;

        case 4:
            b.print();
            break;

        case 5:
            b.clear();
            break;

        case 6:
            cout << "min: " << b.min() << endl;
            cout << "max: " << b.max() << endl;
            break;

        default:
            break;
        }
        cin >> t;
    }
    system("pause");
    return 0;
}