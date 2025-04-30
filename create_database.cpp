#include <chrono>
#include <iostream>

#include "PatternDatabases/CornerDbMaker.h"

using namespace std;

int main() {
  cout << "Creating Corner Pattern Database...\n";
  cout << "This may take several minutes. Please be patient.\n";

  auto start = chrono::high_resolution_clock::now();

  // Create a database maker with the specified filename
  string filename = "corner_pattern_database.bin";
  CornerDbMaker dbMaker(filename);

  // Generate the database through BFS
  cout << "Running BFS to build the database...\n";
  bool success = dbMaker.bfsAndStore();

  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> duration = end - start;

  if (success) {
    cout << "Corner pattern database created successfully!\n";
    cout << "Time taken: " << duration.count() << " seconds.\n";
    cout << "Database saved to: " << filename << "\n";
    cout << "You can now use the Korf IDA* solver with this database.\n";
  } else {
    cout << "Failed to create the corner pattern database.\n";
  }

  return 0;
}