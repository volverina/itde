#include <iostream> // I/O
#include <fstream> // файлові потоки
#include <vector>   // для динамічних масивів
#include <string>   // для динамічних рядків
#include <math.h>  // exp
#include <stdlib.h> // random

using namespace std; // стандартний простір імен

typedef vector<double> dvec; // dvec - нове ім'я vector<double>

// оператор виведення
ostream &operator<<(ostream &s, dvec v)
{
    for(int i=0; i<v.size(); i++)
        s<<v[i]<< " ";
    return s;
}

// оператор уведення
istream &operator>>(istream &s, dvec &v)
{
    for(int i=0; i<v.size(); i++)
        s>>v[i];
    return s;
}

// оператор виведення
ostream &operator<<(ostream &s, vector<int> v)
{
    for(int i=0; i<v.size(); i++)
        s<<v[i]<< " ";
    return s;
}

// оператор уведення
istream &operator>>(istream &s, vector<int> &v)
{
    for(int i=0; i<v.size(); i++)
        s>>v[i];
    return s;
}

// оператор порівняння
bool operator==(dvec a, dvec b)
{
    if(a.size()!=b.size())
        return false;
    for(int i=0; i<a.size(); i++)
        if(a[i]!=b[i])
            return false;
    return true;
}

// нерівність векторів
bool operator!=(dvec a, dvec b)
{
    return !(a==b);
}

// додавання векторів
dvec operator+(dvec a, dvec b)
{
    if(a.size()!=b.size())
        throw string("неможливо додати вектори через різні їх розміри");

    dvec res(a.size());
    for(int i=0; i<a.size(); i++)
        res[i]=a[i]+b[i];
    return res;
}

// множення вектора на скаляр
dvec operator*(dvec a, double c)
{
    dvec res(a.size());
    for(int i=0; i<a.size(); i++)
        res[i]=a[i]*c;
    return res;
}

// множення скаляра на вектор
dvec operator*(double c, dvec a)
{
    return a*c;
}

// вектор, обернений до даного
dvec operator-(dvec a)
{
    return a*(-1);
}

// віднімання векторів: a - b == a + (-b)
dvec operator-(dvec a, dvec b)
{
    if(a.size()!=b.size())
        throw string("неможливо відняти вектори через різні їх розміри");

    return a+(-b);
}

// скалярний добуток векторів
double operator*(dvec a, dvec b)
{
    if(a.size()!=b.size())
        throw string("неможливо помножити вектори через різні їх розміри");

    double res=0;
    for(int i=0; i<a.size(); i++)
        res+=a[i]*b[i];
    return res;
}

typedef vector<dvec> matrix; // матриця

// конструктор матриці
matrix make(int rows, int cols, double *m=0)
{
    if(rows<1 || cols<1)
        throw string("неможливо створити матрицю із такими розмірами");

    matrix res(rows);
    for(int i=0;i<rows;i++)
        res[i]=dvec(cols);
    if(m)
        for(int i=0, number=0;i<rows;i++)
            for(int j=0;j<cols;j++)
                res[i][j]=m[number++];
    return res;
}

// оператор виведення
ostream &operator<<(ostream &s, matrix v)
{
    for(int i=0; i<v.size(); i++)
        s<<v[i]<< endl;
    return s;
}

// оператор уведення
istream &operator>>(istream &s, matrix &v)
{
    for(int i=0; i<v.size(); i++)
        s>>v[i];
    return s;
}


// оператор порівняння
bool operator==(matrix a, matrix b)
{
    if(a.size()!=b.size() || a[0].size()!=b[0].size())
        return false;
    for(int i=0; i<a.size(); i++)
        if(a[i]!=b[i])
            return false;
    return true;
}

// нерівність матриць
bool operator!=(matrix a, matrix b)
{
    return !(a==b);
}


// додавання матриць
matrix operator+(matrix a, matrix b)
{
    if(a.size()!=b.size() || a[0].size()!=b[0].size())
        throw string("неможливо додати матриці через різні їх розміри");

    matrix res(a.size());
    for(int i=0; i<a.size(); i++)
        res[i]=a[i]+b[i];
    return res;
}


// множення матриці на скаляр
matrix operator*(matrix a, double c)
{
    matrix res=a;
    for(int i=0; i<a.size(); i++)
        res[i]=a[i]*c;
    return res;
}


// множення скаляра на матрицю 
matrix operator*(double c, matrix a)
{
    return a*c;
}

// матриця, протилежна до заданої
matrix operator-(matrix a)
{
    return a*(-1);
}

// віднімання матриць: a - b == a + (-b)
matrix operator-(matrix a, matrix b)
{
    if(a.size()!=b.size())
        throw string("неможливо відняти вектори через різні їх розміри");

    return a+(-b);
}

//транспонування вектора
matrix operator~(dvec v)
{
    int rows=1, cols=v.size();
    matrix res=make(cols, rows);
    for(int i=0;i<cols;i++)
        res[i][0]=v[i];
    return res;
}

//транспонування матриці
matrix operator~(matrix v)
{
    int rows=v.size(), cols=v[0].size();
    matrix res=make(cols, rows);
    for(int i=0;i<cols;i++)
        for(int j=0;j<rows;j++)
            res[i][j]=v[j][i];
    return res;
}

//отримати вектор-стовпець із матриці
dvec column(matrix a, int col)
{
    if(col <0 || col >= a[0].size())
        throw string("неможливо отримати стовпець за межами матриці");

    dvec res(a.size());
    for(int i=0;i<a.size();i++)
        res[i]=a[i][col];
    return res;
}

//множення матриць
matrix operator*(matrix a, matrix b)
{
    // res[m1 x n2] = a[m1 x n1] * b [m2 x n2]
    int m1=a.size(), n1=a[0].size(),
        m2=b.size(), n2=b[0].size();
    matrix res = make(m1, n2);

    if(n1!=m2)
        throw string("множення неспівмірних матриць неможливе");

    for(int i=0;i<m1;i++)
        for(int j=0;j<n2;j++)
            res[i][j]= a[i] * column(b, j);
    return res;
}

// класс для реалізації нейронної мережі

//функція активації нейрону
double activate(double s, double alpha=0.5)
{
    return 1/(1+exp(-2*alpha*s)); // наприклад, сигмоїда
}


class neural
{
    string filename; // для збереження нейронної мережі
    vector<int> layers; // вектор, що містить кількість нейронів у кожному шарі мережі
    vector<matrix> weights; // вектор матриць (тензор) вагових коефіцієнтів
    dvec min_input, max_input, min_output, max_output; // вектори для зберігання граничних значень
    void findminmax(); // пошук мінімальних та максимальних значень
    dvec normalize(dvec);// нормалізація входу
    dvec normalize_output(dvec);// нормалізація виходу
    dvec denormalize(dvec);// денормалізація виходу
public:
    matrix patterns_input, patterns_output; // матриці входів та виходів образів
    neural(vector<int>, string); // конструктор нової мережі
    neural(string); // конструктор мережі, збереженої у файлі
    friend ostream &operator<<(ostream &, neural);
    bool load(string s); // завантаження даних для навчання
    dvec forward(dvec); // проходження сигналу через мережу
    void rand(double, double); // встановлення випадкових матриць коефіцієнтів
    double train(double err=0.001,int tries=100000,bool out=false); // стохастичне "навчання" нейронної мережі
    double train_bp(double err=0.001,int tries=100000, double alpha=0.5, double eta=0.3, bool out=false); // "навчання" нейронної мережі
    double geterror(); // поточна помилка навченостi нейронної мережі
    bool savenetwork(string); // збереження архітектури мережі у файлі
    //bool loadnetwork(string); // завантаження архітектури мережі з файлу
};

// конструктор 1
neural::neural(vector<int> v, string fname)
{
    // кількість шарів - не менше за 2
    if(v.size()<2)
        throw string("мінімальна кількість шарів - 2");
    // кількість нейронів на кожному шарі - не менше 1
    for(int i=0;i<v.size();i++)
        if(v[i]<1)
            throw string("кількість нейронів на кожному шарі - не менше 1");
    layers=v;
    // створення матриць вагів
    weights=vector<matrix>(layers.size()-1);
    for(int i=0; i<layers.size()-1; i++)
        weights[i]=make(layers[i]+1, layers[i+1]);
    min_input=max_input=dvec(layers[0]);
    min_output=max_output=dvec(layers[layers.size()-1]);
    filename=fname;
    ofstream(filename)<<(*this);
}


// конструктор 2
neural::neural(string fname)
{
    filename=fname;
    ifstream f(filename);
    if(!f)
        throw string("неможливо відкрити файл мережі "+filename);

    int numlayer; 
    if(!(f>>numlayer))
        throw string("неможливо прочитати з файлу мережі кількість шарів");

    // кількість шарів - не менше за 2
    if(numlayer<2)
        throw string("мінімальна кількість шарів - 2");

    vector<int> v(numlayer);

    if(!(f>>v))
        throw string("неможливо прочитати з файлу мережі кількість нейронів на кожному шарі");

    // кількість нейронів на кожному шарі - не менше 1
    for(int i=0;i<v.size();i++)
        if(v[i]<1)
            throw string("кількість нейронів на кожному шарі - не менше 1");

    layers=v;
    // створення матриць вагів
    weights=vector<matrix>(layers.size()-1);
    for(int i=0; i<layers.size()-1; i++)
    {
        weights[i]=make(layers[i]+1, layers[i+1]);
        if(!(f>>weights[i]))
            throw string("неможливо прочитати з файлу мережі матрицю вагових коефіцієнтів");
    }

    min_input=max_input=dvec(layers[0]);
    min_output=max_output=dvec(layers[layers.size()-1]);

    if(!(f >> min_input >> max_input >> min_output >> max_output))
        throw string("неможливо прочитати з файлу мережі вектори граничних значень");
}



// оператор виведення
ostream &operator<<(ostream &s, neural n)
{
    // архітектура = кількість нейронів на кожному шарі
    s << n.layers.size() << endl << endl;
    s << n.layers << endl << endl;
    // виводимо матриці зв'язків
    for(int i=0;i<n.weights.size();i++)
        s<<n.weights[i]<<endl;
    // вектори для граничних значень
    s << n.min_input << endl << n.max_input  << endl << n.min_output <<  endl  << n.max_output << endl; 
    return s;
}


bool neural::load(string s) // завантаження даних для навчання
{
    ifstream f(s);
    if(!f)//помилка відкриття файлу
    {
        cerr<<"помилка відкриття файлу "<<s<<endl;
        return false;
    }
    int numpat, numinput, numoutput;
    if(!(f>>numpat >> numinput >> numoutput))
    {
        cerr<<"помилка читання файлу "<<endl;
        return false;// помилка читання
    }
    if(numpat<1)
    {
        cerr<<"кількість образів має бути натуральним числом"<<endl;
        return false;
    }
    if(numinput!=layers[0] || numoutput!=layers[layers.size()-1])
    {
        cerr<<"кількість нейронів на вході та виході у мережі та файлі різняться"<<endl;
        return false;
    }

    patterns_input=make(numpat, numinput);
    patterns_output=make(numpat, numoutput);

    for(int i=0;i<numpat;i++)
        if(!(f>>patterns_input[i]>>patterns_output[i]))
        {
            cerr<<"помилка читання з файлу"<<endl;
            return false;
        }
    findminmax();
    return true;
}

void neural::findminmax()
{
    min_input=max_input=patterns_input[0];
    min_output=max_output=patterns_output[0];

    for(int i=1;i<patterns_input.size();i++)
    {
        for(int j=0;j<patterns_input[0].size();j++)
        {
            if(patterns_input[i][j]<min_input[j])
                min_input[j]=patterns_input[i][j];
            if(patterns_input[i][j]>max_input[j])
                max_input[j]=patterns_input[i][j];
        }
        for(int j=0;j<patterns_output[0].size();j++)
        {
            if(patterns_output[i][j]<min_output[j])
                min_output[j]=patterns_output[i][j];
            if(patterns_output[i][j]>max_output[j])
                max_output[j]=patterns_output[i][j];
        }
    }
}

dvec neural::normalize(dvec x)// нормалізація входу
{
    dvec res=x;

    for(int i=0;i<x.size();i++)
        if(max_input[i]!=min_input[i])
            res[i]=(x[i]-min_input[i])/(max_input[i]-min_input[i]);
        else 
            res[i]=(x[i]-min_input[i])/0.0001;
    return res;
}

dvec neural::normalize_output(dvec x)// нормалізація виходу
{
    dvec res=x;

    for(int i=0;i<x.size();i++)
        if(max_output[i]!=min_output[i])
            res[i]=(x[i]-min_output[i])/(max_output[i]-min_output[i]);
        else 
            res[i]=(x[i]-min_output[i])/0.0001;
    return res;
}

dvec neural::denormalize(dvec y)// денормалізація виходу
{
    dvec res=y;

    for(int i=0;i<y.size();i++)
        if(max_output[i]!=min_output[i])
            res[i]=y[i]*(max_output[i]-min_output[i])+min_output[i];
        else 
            res[i]=y[i]*0.0001+min_output[i];
    return res;
}

// створення матриці-рядка з вектору
matrix make(dvec v)
{
    matrix res(1);
    res[0]=v;
    return res;
}

// застосування функції активації до вектора
dvec apply(dvec s, double alpha=0.5)
{
    dvec res=s;

    for(int i=0;i<s.size();i++)
        res[i]=activate(s[i], alpha);
    return res;
}

// обчислення виходу за вхідним значенням
dvec neural::forward(dvec x) // проходження сигналу через мережу
{
    x=normalize(x);

    for(int i=0;i<weights.size();i++)
    {
        x.push_back(1); // нейрон зміщення - bias
        matrix xn=make(x);
        matrix s=xn*weights[i];
        dvec y=apply(s[0]);
        x=y;
    }

    return denormalize(x);
}

void neural::rand(double low, double high) // встановлення випадкових матриць коефіцієнтів
{
    for(int i=0;i<weights.size();i++)
        for(int j=0;j<weights[i].size();j++)
            for(int k=0;k<weights[i][0].size();k++)
                weights[i][j][k]=(random()/double(RAND_MAX))*(high-low)+low;
}


double neural::geterror() 
{
    double error=0;

    for(int i=0;i<patterns_input.size();i++)
    {
        dvec yc=forward(patterns_input[i]);
        error+= 0.5*(patterns_output[i]-yc)*(patterns_output[i]-yc);
    }
    //error/=patterns_input.size();

    return error;
}


// "навчання" нейронної мережі методом зворотного поширення помилки
double neural::train_bp(double err,int NUMBER_OF_STEPS, double alpha, double eta, bool out) 
{
    double error=err+1, newerror;
    
    // створення матриць змін звагів
    vector<matrix> deltaweights=vector<matrix>(layers.size()-1);
    for(int i=0; i<layers.size()-1; i++)
        deltaweights[i]=make(layers[i]+1, layers[i+1]);

    double olderror=geterror();
    //Повторити NUMBER_OF_STEPS раз:
    for(int numtries=0;error>err && numtries<NUMBER_OF_STEPS;numtries++)
    {
        error=0;

        int m=patterns_input.size();
        for(int d=0;d<m;d++)//Для всіх d від 1 до m:
        {
            // Подати {\displaystyle \{x_{i}^{d}\}}{\displaystyle \{x_{i}^{d}\}} на вхід сітки і підрахувати виходи {\displaystyle o_{i}}{\displaystyle o_{i}} кожного вузла.
            vector<dvec> outputs;

            dvec x=normalize(patterns_input[d]), y;
            dvec saved_input=x;

            for(int i=0;i<weights.size();i++)
            {
                x.push_back(1); // нейрон зміщення - bias
                matrix xn=make(x);
                matrix s=xn*weights[i];
                y=apply(s[0], alpha);
                outputs.push_back(y);
                x=y;
            }

            dvec yc=denormalize(y);
            error+= 0.5*(patterns_output[d]-yc)*(patterns_output[d]-yc);

            //Для всіх { k\in Outputs}{\displaystyle k\in Outputs}
            //{ \delta _{k}=o_{k} (1-o_{k})(t_{k}-o_{k})}
            
            vector<dvec> deltas=outputs;

            int last=outputs.size()-1;
            for(int k=0;k<outputs[last].size();k++)
            {
                dvec t=normalize_output(patterns_output[d]);
                deltas[last][k]=outputs[last][k]*(1-outputs[last][k])*(t[k]-outputs[last][k]);
            }

            // Для кожного рівня l, починаючи з останнього
            for(int l=last-1;l>=0;l--)
                //Для кожного вузла j рівня l порахувати
                for(int j=0;j<outputs[l].size();j++)
                //{\delta _{j}=o_{j}(1-o_{j})    \sum _{k\in Children(j)}\delta _{k}w_{j,k}}
                {
                    double sum=0;

                    for(int k=0;k<deltas[l+1].size();k++)
                        sum+=deltas[l+1][k]*weights[l+1][j][k];

                    deltas[l][j]=outputs[l][j]*(1-outputs[l][j])*sum;
                }

            outputs.insert(outputs.begin(), saved_input);
            for(int l=0;l<deltaweights.size();l++)
            {
                //Для кожного ребра сітки {i, j}
                for(int i=0;i<deltaweights[l].size();i++)
                    for(int j=0;j<deltaweights[l][i].size();j++)
                        //{ \Delta w_{i,j}=\alpha \Delta w_{i,j}+(1-\alpha )\eta \delta _{j}o_{i}}
                        deltaweights[l][i][j]=alpha*deltaweights[l][i][j] +(1-alpha)*eta
                            *deltas[l][j]*outputs[l][i]; //?????

                //{ w_{i,j}=w_{i,j}+\Delta w_{i,j}}
                weights[l]=weights[l]+deltaweights[l];
                /*
                    Без зайвих кроків
                */
                double newerror=geterror();
                if(newerror>olderror)
                    weights[l]=weights[l]-deltaweights[l];
                else
                    olderror=newerror;
            }      
        }
        savenetwork(filename);
        if(out)
            cout<<"Поточна помилка = "<<error<<" після "<<numtries <<" кроків"<<endl;
    }
    
    return error;
}


double neural::train(double err, int tries, bool out) // "навчання" нейронної мережі
{
    double error=err+1, newerror;
    int numtries=0;

    while(error>err && numtries<tries)
        for(;;)
        {
            error=geterror();
            vector<matrix> saved_weights=weights;// матриці вагових коефіцієнтів до зміни
            rand(-0.15,0.15); // встановлюю випадкові вагові коефіцієнти
            // додавання до збережених вагів випадкових змін
            for(int i=0;i<weights.size();i++)
                weights[i]=saved_weights[i]+weights[i];
            newerror=geterror();
            if(newerror<error)
            {
                savenetwork(filename);
                error=newerror;
                if(out)
                    cout<<"Поточна помилка = "<<error<<" після "<<numtries <<" кроків"<<endl;
                break;
            }
            else
                weights=saved_weights;
            numtries++;
            if(numtries>tries)
                break;
        }
    
    return error;
}

bool neural::savenetwork(string filename) // збереження архітектури мережі у файлі
{
    ofstream f(filename);

    if(!f)
        return false;
    if(f<<(*this))
        return true;
    else 
        return false;
}


int main()
{
    vector<int> v={16, 32, 48, 24, 16, 7, 3, 6, 3};
    //vector<int> v={16, 32, 48, 24, 16, 7, 3, 3};
    //neural net(v, "network_bp.txt");

    neural net("network_bp.txt");
    
    if(!net.load("/home/cc/Documents/2022_04_12/patterns.txt"))
    {
        cout<<"помилка завантаження файлу"<<endl;
        return 1;
    }

    //net.rand(-20,+20); // встановлення випадкових значень для train_bp
/*
    net.rand(-0.1,+0.1); // встановлення випадкових значень для train_bp
    //cout<<net.patterns_input <<endl << net.patterns_output <<endl;
    cout<<net<<endl;
*/
    for(int i=0;i<net.patterns_input.size();i++)
    {
        dvec yc=net.forward(net.patterns_input[i]);

        cout<<"Для входу "<<net.patterns_input[i] << " та виходу " <<net.patterns_output[i] << 
        " отримали значення "<<yc<<endl;
    }
    double error=net.geterror();
    cout << "Помилка до навчання = " << error << endl;

    //error=net.train(0.00001, 100000, true);
    error=net.train_bp(0.000001, 100000, 0.5, 90, true);
    cout << "Помилка після навчання = " << error << endl;

    for(int i=0;i<net.patterns_input.size();i++)
    {
        dvec yc=net.forward(net.patterns_input[i]);

        cout<<"Для входу "<<net.patterns_input[i] << " та виходу " <<net.patterns_output[i] << 
        " отримали значення "<<yc<<endl;
    }


    /*
    double m1[]={1, 2, 3, 4, 5, 6},
    m2[]={-1, -2, -3, -4, -5, 6};

    matrix a=make(2, 3, m1), b=make(3, 2, m2);

    cout << "A :" << endl << a << endl;
    cout << "B :" << endl << b << endl;

    try
    {
        matrix c=a*b;
        cout << "C :" << endl << c << endl;
    }
    catch(string msg)
    {
        std::cerr << msg << '\n';
    }
    */
/*
    if(a!=b)
        cout <<"A не дорівнює B"<<endl;
    else
        cout <<"A дорівнює B"<<endl;
        */
//    cout << "Уведіть матрицю A: ";
//    cin >> a;
//    cout << endl << "A :" << endl << a << endl;

    /*
    dvec a(3), b(4);

    a[0]=1, a[1]=10, a[2]=-1;
    b[0]=-2, b[1]=2, b[2]=12;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
     //dvec c=a+b;


    double c;

    try
    {
        c=a*b;
        cout << "c = " << c << endl;
    }
    catch(string msg)
    {
        cerr<<"щось пішло не так... "<<msg << endl;
    }

    if(a!=b)
        cout <<"a не дорівнює b"<<endl;
    else
        cout <<"a дорівнює b"<<endl;
    */
    /*
    dvec v(3);

    cout << "v =" << v << endl;
    cout << "Уведіть v: ";
    cin >> v;
    cout << "v =" << v << endl;
    */
    return 0;
}