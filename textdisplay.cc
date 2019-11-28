// //textdisplay.cc
// #include <iomanip>
// #include "subject.h"
// #include "textdisplay.h"
// using namespace std;


// TextDisplay::TextDisplay(int n): gridSize{n} {
// 	// Initialize the 2D vector space with '-'
// 	for (int y = 0; y < gridSize; ++y) {
// 		vector<char> row;
// 		for (int x = 0; x < gridSize; ++x) {
//             // Replace with space, use this to for better information
// 			row.emplace_back('-');
// 		}
// 		theDisplay.emplace_back(row);
// 	}
// };

// // When a cell is changed, text display updates itself
// void TextDisplay::notify(Subject<BoardInfo, BoardState> &whoNotified) {
// 	State state = whoNotified.getState();
// 	Info info = whoNotified.getInfo();

// 	if (state.type == UpdateType::BoardChange) {
		
// 	} else if (state.type == UpdateType::LevelChange) {
		
// 	}
// }

// void TextDisplay::drawBoards(std::ostream &out) {
//     for 
//     out << "Level:" << setw(5) << bi.level->getLevel();
// }

// // Print the 2D char array
// std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
// 	for (int y = 0; y < td.gridSize; ++y) {
// 		for (int x = 0; x < td.gridSize; ++x) {
// 			out << td.theDisplay[y][x];
// 		}
// 		out << endl;
// 	}
// 	return out;
// }
