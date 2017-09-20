#include "input_int_valid.h"

using namespace std;

int input_int_valid(string x) {
    char s[80];
    double d;
    char c;
    int i;
    int a =0;
    char *step;
    while (a<6) {
        cout << x.c_str()<<" is:";
        fflush(stdout);
        rewind(stdin);
        fgets(s,80,stdin);
        if (2==sscanf(s,"%d%c",&i,&c) && strtod(s,&step)>=0)
        {
            if ('\n'==c) {
                break;
            }
        }
        if ('\n'==s[strlen(s)-1] || strtod(s,&step)<0)
        {
            s[strlen(s)-1]=0;
            ++a;
            if(a<5)
            {
                if (strtod(s,&step)<0)
                    cout << x.c_str() << " cannot be negative number, please enter again,you have  " << 5-a << "  chances left "<<endl;
                else
                    cout << x.c_str() << " should be a integer, please enter again, you have  " << 5-a << "  chances left "<<endl;
            }
            else
            {
                if (strtod(s,&step)<0)
                    cout << x.c_str() << " cannot be negative number, please enter again,you have  " << 5-a << "  chances left "<<endl;
                else
                    cout << x.c_str() << " should be a integar, please enter again, you have  " << 5-a << "  chances left "<<endl;
                cout << "Input error, system will exit" << endl;
                exit(0);
            }
            
        }
    }
    d=strtoul(s,NULL,0);
    return d;
    
    
}

