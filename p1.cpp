#include <iostream> 
#include <string>
#include <fstream> 
#include <sstream> 
#include <cctype> 
#include <iomanip>
#include <climits>

using namespace std;

void Print(const string& filename, int columnWidth);
void Commands(const string& filename, int columnWidth);
void ColNames(const string& filename);
void SearchColNameValue(const string& filename, int columnWidth);
void MinColName(const string& filename);
void MaxColName(const string& filename);
void AvgColName(const string& filename);
bool hasQuotes(const string& str);
string whiteSpace(const string & str);

int main(int argc, char* argv[]){
    
    string filename;
    // getline(cin, filename);
    int columnWidth;

    // Invalid number of command-line arguments
    if (argc != 3){
        cout << "Usage: ./a database.csv #col_width" << endl;;
        return 1;
    }
    else{
        filename = argv[1];
        columnWidth = stoi(argv[2]);
    }
    
    ifstream cvsFile(filename);
    if(!cvsFile.is_open()){
        cout << "Failed to open \"" << filename << "\"" << endl;
        return 1;
    }

    cvsFile.close();
    
    cout << "Enter a command or \"help\" for a command list:" << endl;
    while (true){
    Commands(filename, columnWidth);
    cout << endl;
    //Print(argc, argv, filename, columnWidth);
    }

    return 0;
}

// Function to call rest of functions depending on what the user types in
void Commands(const string& filename, int columnWidth){
    
    
    string userString;
    while(userString != "quit"){
        cin >> userString; // Only read the first word
        // cout << "Enter a command or \"help\" for a command list:" << endl;

        if (userString == "quit"){
            exit(0);
        }
        else if (userString == "help"){
            cout << "command list:" << endl; 
            cout << "print" << endl;
            cout << "cols" << endl;
            cout << "search *|col_name val" << endl;
            cout << "min col_name" << endl;
            cout << "max col_name" << endl;
            cout << "avg col_name" << endl;
            cout << endl;
            cout << "Enter a command or \"help\" for a command list:" << endl;
        }
        else if (userString == "print"){
            Print(filename, columnWidth);
            cout << endl;
            cout << "Enter a command or \"help\" for a command list:" << endl;
        }
        else if (userString == "cols"){
            ColNames(filename);
            cout << endl;
            cout << "Enter a command or \"help\" for a command list:" << endl;
        }
        else if (userString == "search"){
            SearchColNameValue(filename, columnWidth);
            cout << endl;
            cout << "Enter a command or \"help\" for a command list:" << endl;
        }
        else if (userString == "min"){
            MinColName(filename);
            cout << endl;
            cout << "Enter a command or \"help\" for a command list:" << endl;
        }
        else if (userString == "max"){
            MaxColName(filename);
            cout << endl;
            cout << "Enter a command or \"help\" for a command list:" << endl;
        }
        else if (userString == "avg"){
            AvgColName(filename);
            cout  << endl;
            cout << "Enter a command or \"help\" for a command list:" << endl;
        }
        else{
            cout << "Invalid command" << endl;
            cout << "Enter a command or \"help\" for a command list:" << endl;
        }
        //cout << "Enter a command or \"help\" for a command list:" << endl; 
        //cin >> userString;
    }
}


// Print all rows and columns. Each column should be printed with a width equal to the second command line argument
void Print (const string& filename, int columnWidth){
    ifstream csvFile(filename);
    if(!csvFile.is_open()){
        cout << "Failed to open " << "\"" << filename << "\"" << endl;
        return; // Don't need 1
    }

    string line;
    int rowCount = 0;
    while (getline(csvFile, line) && rowCount <= 5000){ // reads source file line by line
        istringstream iss(line);
        
        string token;
        int colCount = 0;
        while(getline(iss, token, ',') && colCount <= 50){ // Take and output comma by comma
            cout << setw(columnWidth) << right << token;
            
            //cout << setw(columnWidth) << right << token;
            colCount++;
            /*if (lastCol){
                cin >> token;
                if(token.empty()){
                    cout << setw(columnWidth) << right << " ";
                }
            }*/
        }
        int commaCount = 0;
        for(int i = 0; i < line.length(); i++){
            if (line[i] == ','){
            commaCount++;
            }
        }
        if (colCount < commaCount + 1){
            cout << setw(columnWidth) << right << "";
        }
        cout << endl;
        rowCount++;
    }
    //cout << lastColToken;
    csvFile.close();
}

// Print all column names with each appearing on a new line
void ColNames(const string& filename){
    ifstream csvFile(filename);
    if(!csvFile.is_open()){
        cout << "Failed to open " << "\"" << filename << "\"" << endl;
        return; // Don't need 1
    }

    string firstLine;
    if (getline(csvFile, firstLine)){ // reads only 1st line
        istringstream iss(firstLine);
        
        string token;
        int colCount = 0;
        while(getline(iss, token, ',') && colCount <= 50){ // Take and output comma by comma
            cout << token << endl;
        }
        cout << endl;
    }
    csvFile.close();
}

/**Formatted print all rows where the value in column col_name equals the value. Each column should be printed with a width equal to the second command line argument.
If col_name is *, then print any rows where the value appears in any column in the row. If a value appears in a row more than once, only print the row once.
If no rows match, print "No results".*/


void SearchColNameValue(const string& filename, int columnWidth){
    ifstream csvFile(filename);
    if(!csvFile.is_open()){
        cout << "Failed to open " << "\"" << filename << "\"" << endl;
        return; // Don't need 1
    }


    string input;
    getline(cin, input);

    size_t lastSpace = input.find_last_of(' ');

    string colName = input.substr(0, lastSpace);
    colName = colName.substr(1);

    string value = input.substr(lastSpace + 1);


    if (hasQuotes(colName)){
        colName = colName.substr(1, colName.size()-2);
    }
    if (hasQuotes(value)){
        value = value.substr(1, value.size()-2);
    }

    /*if (colName.empty()){
        cout << "Invalid column \"" << colName << "\"" << endl;
        return;
    }
    else if (value.empty()){
        cout << "No results" << endl;
        return;
    }*/


    // cout << colName << endl;
    // cout << value << endl;

    int comma = 0;
    string firstLine;
    string asterisk = "*";

    if (getline(csvFile, firstLine)){ // reads only 1st line
        istringstream iss(firstLine);

        string commaToken;
        while(getline(iss, commaToken, ',')){
            
            if(colName != commaToken){
                comma++;
            }
            else{
                colName = commaToken;
                break;
            }
        }
        if (colName != commaToken && colName != asterisk){
            cout << "Invalid column \"" << colName << "\"" << endl;
            return;
        }
        else if (colName.empty()){
        cout << "Invalid column \"" << colName << "\"" << endl;
        return;
        }
        else if (value.empty()){
            cout << "No results" << endl;
            return;
        }
        else{
            csvFile.clear();
            csvFile.seekg(0, ios::beg);

            string newFirstLine;
            if (getline(csvFile, newFirstLine)){ // reads source file line by line
                istringstream iss(newFirstLine);
        
                string token;
                while(getline(iss, token, ',')){ // Take and output comma by comma
                    cout << setw(columnWidth) << right << token;
            
                }
                cout << endl;
            }
        }
    }

    string line;
    bool found = false;
    int colCount = 0;

    while (getline(csvFile, line)){
        istringstream iss(line);
        string token;
        bool valFoundInLine = false;
        while (getline(iss, token, ',')){
            //cout << setw(columnWidth) << right << token;
            if (token == value) {
                found = true;
                valFoundInLine = true;
            }
            //cout << setw(columnWidth) << right << token;
            colCount++;
        }
        // cout << endl;
        if (valFoundInLine){
            istringstream tokenStream(line);
            while (getline(tokenStream, token, ',')){
            cout << setw(columnWidth) << right << token;
            }
            cout << endl;
        }
        /*if (found) {
            cout << setw(columnWidth) << right << line << endl;
            break; // Print only the first occurrence
        
        }*/
    }
    
    int commaCount = 0;
        for(int i = 0; i < line.length(); i++){
            if (line[i] == ','){
            commaCount++;
            }
        }
        if (colCount < commaCount + 1){
            cout << setw(columnWidth) << right << "";
        }

    if (!found) {
        cout << "No results" << endl;
    }

     csvFile.close();

}




/*Determine the minimum value in the column col_name. Ignore rows with blank values.
Output: "The min for col "C" = X" where C is the column and X is the min or "N/A" if the min cannot be computed (all cells blank).
*/
void MinColName(const string& filename){
    ifstream csvFile(filename);
    if(!csvFile.is_open()){
        cout << "Failed to open " << "\"" << filename << "\"" << endl;
        return; // Don't need 1
    }


    string userCol;
    getline(cin, userCol);

    if (hasQuotes(userCol)){
        userCol = userCol.substr(1, userCol.size()-2);
    }

    if (userCol.empty()){
        cout << "Invalid column \"" << userCol << "\"" << endl;
        return;
    }
    userCol = userCol.substr(1);
    
    int comma = 0;
    string firstLine;

    if (getline(csvFile, firstLine)){ // reads only 1st line
        istringstream iss(firstLine);

        string commaToken;
        while(getline(iss, commaToken, ',')){
            if(userCol != commaToken){
                comma++;
            }
            else{
                userCol = commaToken;
                break;
            }
        }
        if (userCol != commaToken){
            cout << "Invalid column \"" << userCol << "\"" << endl;
        }
    }
    
    double min;
    bool assign = false;
    string line;
    int row = 0;
    bool empty = true;

    while (getline(csvFile, line)){ // reads source file line by line
        istringstream iss(line);
        for(int i = 0; i < comma + 1; i++){
            getline(iss, line, ',');
        }
        if(!line.empty()){
            double start = stod(line); // Could change back to stod
            if(assign == false){
                assign = true;
                min = start;
                row++;
                empty = false;
            }
            else if (start < min){
                min = start;
            }
        }
     }
    if (empty == false){
            cout << "The min for col \"" << userCol << "\" = " << min << endl;
        }
        else{
            cout << "The min for col \"" << userCol << "\" = N/A" << endl;
        }
    csvFile.close();

}

/*Determine the maximum value in the column col_name. Ignore rows with blank values.
Output: "The max for col "C" = X" where C is the column and X is the max or "N/A" if the max cannot be computed (all cells blank).
*/
void MaxColName(const string& filename){
    ifstream csvFile(filename);
    if(!csvFile.is_open()){
        cout << "Failed to open " << "\"" << filename << "\"" << endl;
        return; // Don't need 1
    }


    string userCol;
    getline(cin, userCol);

    if (hasQuotes(userCol)){
        userCol = userCol.substr(1, userCol.size()-2);
    }

    if (userCol.empty()){
        cout << "Invalid column \"" << userCol << "\"" << endl;
        return;
    }
    userCol = userCol.substr(1);
    
    int comma = 0;
    string firstLine;

    if (getline(csvFile, firstLine)){ // reads only 1st line
        istringstream iss(firstLine);

        string commaToken;
        while(getline(iss, commaToken, ',')){
            if(userCol != commaToken){
                comma++;
            }
            else{
                userCol = commaToken;
                break;
            }
        }
        if (userCol != commaToken){
            cout << "Invalid column \"" << userCol << "\"" << endl;
        }
    }
    
    double max;
    bool assign = false;
    string line;
    int row = 0;
    bool empty = true;

    while (getline(csvFile, line)){ // reads source file line by line
        istringstream iss(line);
        for(int i = 0; i < comma + 1; i++){
            getline(iss, line, ',');
        }
        if(!line.empty()){
            double start = stod(line); // Could change back to stod
            if(assign == false){
                assign = true;
                max = start;
                row++;
                empty = false;
            }
            else if (start > max){
                max = start;
            }
        }
     }
    if (empty == false){
            cout << "The max for col \"" << userCol << "\" = " << max << endl;
        }
        else{
            cout << "The max for col \"" << userCol << "\" = N/A" << endl;
        }
    csvFile.close();

}

/*Calculate the average value in the column col_name. Ignore rows with blank values.
Output: "The avg for col "col_name" = X" where C is the column and X is the average or "N/A" if the average cannot be computed (all cells blank).*/
void AvgColName(const string& filename) {
    ifstream csvFile(filename);
    if (!csvFile.is_open()) {
        cout << "Failed to open \"" << filename << "\"" << endl;
        return;
    }

    string userCol;
    getline(cin, userCol);

    if (hasQuotes(userCol)) {
        userCol = userCol.substr(1, userCol.size() - 2);
    }

    if (userCol.empty()) {
        cout << "Invalid column \"" << userCol << "\"" << endl;
        return;
    }

    userCol = userCol.substr(1);

    int comma = 0;
    string firstLine;

    if (getline(csvFile, firstLine)){ // reads only 1st line
        istringstream iss(firstLine);

        string commaToken;
        while (getline(iss, commaToken, ',')){
            if (userCol != commaToken) {
                comma++;
            } else {
                userCol = commaToken;
                break;
            }
        }

        if (userCol != commaToken){
            cout << "Invalid column \"" << userCol << "\"" << endl;
            return;
        }
    }

    double sum = 0.0;
    int count = 0;
    string line;

    while (getline(csvFile, line)){ // reads source file line by line
        istringstream iss(line);
        string token;
        for (int i = 0; i <= comma; i++){
            getline(iss, token, ',');
        }
        if (!token.empty()){
            istringstream tokenStream(token); // Convert string to double
            double value;
            tokenStream >> value;
            if (!tokenStream.fail()){
                sum += value;
                count++;
            }
        }
    }

    csvFile.close();

    if (count > 0){
        double avg = sum / count;
        cout << "The avg for col \"" << userCol << "\" = " << avg << endl;
    } 
    else{
        cout << "The avg for col \"" << userCol << "\" = N/A" << endl;
    }
}


bool hasQuotes(const string& str) {
    return str.find('"') != string::npos;
}

string whiteSpace(const string & str){
    size_t start = 0;
    size_t end = str.length() - 1;

    while (start <= end && isspace(str[start])){
        start++;
    }
    while (end > start && isspace(str[end])){
        end--;
    }

    return str.substr(start, end-start+1);
}