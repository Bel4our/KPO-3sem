#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Data {
    wchar_t character;
    int number;
};


void serialize(const string& filename, const vector<Data>& data)
{
    ofstream file(filename, ios::binary);
    if (file.is_open())
    {
        for (const auto& item : data) 
        {
            file.put('C'); 
            int charSize = sizeof(item.character);
            file.write(reinterpret_cast<char*>(&charSize), sizeof(charSize)); 
            file.write(reinterpret_cast<const char*>(&item.character), charSize); 

            file.put('I');
            int intSize = sizeof(item.number);
            file.write(reinterpret_cast<char*>(&intSize), sizeof(intSize)); 
            file.write(reinterpret_cast<const char*>(&item.number), intSize); 
        }
        file.close();
    }
    else {
        cerr << "Ошибка записи в файл" << endl;
    }
}
int main() 
{

    vector<Data> data = {
        {u'A', 246}, 
        {u'B', 132523}, 
        {u'C', 543521} 
    };

    string outputPath = "..\\Deserealizer\\data.bin";
    setlocale(LC_ALL, "rus");
    serialize(outputPath, data);

    cout << "Сериализовнао в " << outputPath << endl;

    return 0;
}
