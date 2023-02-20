#include <iostream>;
#include <fstream>;
#include <string>;

using std::cout;

int main() {
	char in[10];
	int programmers[5][5];
	int departments[5][5];
	int assignments[5] = { 0 };
	int progTaken[5] = { 0 };
	int depIndices[5] = { 0 };

	std::ifstream inFile;
	inFile.open("data.txt");

	for (int i = 0;i < 5;i++) {
		inFile.getline(in, 10);
		int j = 0;
		int dep = 0;
		while (in[j] != '\0') {
			if (in[j] != ' ') {
				departments[dep][i] = int(in[j])-'0';
				dep++;
			}
			j++;
		}
	}

	for (int i = 0;i < 5;i++) {
		inFile.getline(in, 10);
		int j = 0;
		int pro = 0;
		while (in[j] != '\0') {
			if (in[j] != ' ') {
				programmers[pro][i] = in[j]-'0';
				pro++;
			}
			j++;
		}
	}
	
	inFile.close();

	for (int dep = 0;dep < 5;dep++) {
		while (assignments[dep] == 0) {
			if (assignments[dep] == 0) {
				while (progTaken[departments[dep][depIndices[dep]]-1] == 1) {
					depIndices[dep]++;
				}

				int whichProg;
				for (int progChoice = 0;progChoice < 5;progChoice++) {

					int sameChoice[5] = { 0 };
					sameChoice[dep] = 1;
					for (int compareDep = dep + 1;compareDep < 5;compareDep++) {
						while (progTaken[departments[compareDep][depIndices[compareDep]]-1]==1 && assignments[compareDep]==0) {
							depIndices[compareDep]++;
						}
						if (departments[dep][depIndices[dep]] == departments[compareDep][depIndices[compareDep]]) {
							sameChoice[compareDep] = 1;
						}
					}

					whichProg = departments[dep][depIndices[dep]] - 1;
					if ((sameChoice[programmers[whichProg][progChoice] - 1] == 1) && progTaken[whichProg] != 1) {
						assignments[programmers[whichProg][progChoice] - 1] = whichProg + 1;
						progTaken[whichProg] = 1;

						sameChoice[programmers[whichProg][progChoice] - 1] = 0;
						for (int updateIndex = 0;updateIndex < 5;updateIndex++) {
							if (sameChoice[programmers[whichProg][updateIndex] - 1] == 1) {
								depIndices[programmers[whichProg][updateIndex] - 1]++;
							}
						}
					}
				}
			}
		}
	}

	for (int i = 0;i < 5;i++) {
		cout << "Dep " << i+1 << " gets programmer num " << assignments[i];
		cout << '\n';
	}
	return 0;
}
