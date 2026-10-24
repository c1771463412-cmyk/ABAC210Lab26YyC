// COMSC-210-5293 | Lab 26 | Yuyi Chen

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <chrono>
#include <string>
using namespace std;
using namespace std::chrono;

const int WIDTH = 15;
const int SIMULATIONS = 15;

int main() {
    // Store the time results for each race
    long long results[2][4][3] = {0};

    // Run the races 15 times
    for (int sim = 0; sim < SIMULATIONS; sim++) {
        vector<string> vec;
        list<string> lst;
        set<string> st;
    

        //-------------
        // Reading Race
        //-------------

        ifstream fin("codes.txt");

        if (!fin) {
            cout << "Error opening file." << endl;
            return 1;
        }

        string word;

        // Start timing vector reading
        auto start = high_resolution_clock::now();

        while (fin >> word) {
            vec.push_back(word);
        }

        // End timing vector reading
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<nanoseconds>(end - start);

        results[0][0][0] = duration.count();

        fin.close();

        //-----------------------------------------------------
        // Open the file again for list reading
        fin.open("codes.txt");

        if (!fin) {
            cout << "Error opening file." << endl;
            return 1;
        }

        // Start timing list reading
        start = high_resolution_clock::now();

        while (fin >> word) {
            lst.push_back(word);
        }

        // End timing list reading
        end = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);

        results[0][0][1] = duration.count();

        fin.close();

        //-----------------------------------------------------
        // Open the file again for set reading
        fin.open("codes.txt");

        if (!fin) {
            cout << "Error opening file." << endl;
            return 1;
        }

        // Start timing set reading
        start = high_resolution_clock::now();

        while (fin >> word) {
            st.insert(word);
        }

        // End timing set reading
        end = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);

        results[0][0][2] = duration.count();

        fin.close();

        //-------------
        // Sorting Race
        //-------------

        // Start timing vector sorting
        start = high_resolution_clock::now();

        sort(vec.begin(), vec.end());

        // End timing vector sorting
        end = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);

        results[0][1][0] = duration.count();

        //-----------------------------------------------------
        // Start timing list sorting
        start = high_resolution_clock::now();

        lst.sort();

        // End timing list sorting
        end = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);

        results[0][1][1] = duration.count();

        //-----------------------------------------------------
        // Set is already sorted
        long long setSortTime = -1;

        results[0][1][2] = setSortTime;

        //---------------
        // Inserting Race
        //---------------

        // Start timing vector inserting
        start = high_resolution_clock::now();

        vec.insert(vec.begin() + vec.size() / 2, "TESTCODE");

        // End timing vector inserting
        end = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);

        results[0][2][0] = duration.count();

        //-----------------------------------------------------
        // Find the middle of the list
        auto it = lst.begin();

        for (int i = 0; i < lst.size() / 2; i++) {
            it++;
        }

        // Start timing list inserting
        start = high_resolution_clock::now();

        lst.insert(it, "TESTCODE");

        // End timing list inserting
        end = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);

        results[0][2][1] = duration.count();

        //-----------------------------------------------------
        // Start timing set inserting
        start = high_resolution_clock::now();

        st.insert("TESTCODE");

        // End timing set inserting
        end = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);

        results[0][2][2] = duration.count();

        //--------------
        // Deleting Race
        //--------------

        // Start timing vector deleting
        start = high_resolution_clock::now();

        vec.erase(vec.begin() + vec.size() / 2);

        // End timing vector deleting
        end = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);

        results[0][3][0] = duration.count();

        //-----------------------------------------------------
        // Find the middle of the list
        auto itDelete = lst.begin();

        for (int i = 0; i < lst.size() / 2; i++) {
            itDelete++;
        }

        // Start timing list deleting
        start = high_resolution_clock::now();

        lst.erase(itDelete);

        // End timing list deleting
        end = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);

        results[0][3][1] = duration.count();

        //-----------------------------------------------------
        // Find the middle of the set
        auto itSetDelete = st.begin();

        for (int i = 0; i < st.size() / 2; i++) {
            itSetDelete++;
        }

        // Start timing set deleting
        start = high_resolution_clock::now();

        st.erase(itSetDelete);

        // End timing set deleting
        end = high_resolution_clock::now();

        duration = duration_cast<nanoseconds>(end - start);

        results[0][3][2] = duration.count();

        // Add the current results to the total times
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                results[1][i][j] += results[0][i][j];
            }
        }
    } // End of simulation loop

    /*****************************************************/
    //-----------------------------------------------------
    // Display the final race results
    string raceNames[4] = {
        "Reading",
        "Sorting",
        "Inserting",
        "Deleting"
    };

    cout << "\nData Structures Races (nanoseconds)\n";

    cout << left << setw(WIDTH) << "Operation"
         << right << setw(WIDTH) << "Vector"
         << setw(WIDTH) << "List"
         << setw(WIDTH) << "Set" << endl;

    for (int i = 0; i < 4; i++) {
        cout << left << setw(WIDTH) << raceNames[i];

        for (int j = 0; j < 3; j++) {
            cout << right << setw(WIDTH) << results[1][i][j];
        }

        cout << endl;
    }

    return 0;
}