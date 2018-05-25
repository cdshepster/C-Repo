#include <iostream>
#include <deque>

bool contains(std::deque<int>& memory, int i){
    for (int &it : memory) {
        if(it == i){
            return true;
        }
    }
    return false;
}

using namespace std;

int main(){
    srand(time(NULL));

    int sequences = 100;
    int sequenceLen = 1000;
    int numBank = 250;
    int numFrames = 100;

    int count = 0;

    cout << "Length of memory reference string: " << sequenceLen << '\n';
    cout << "Frames of physical memory: " << numFrames << '\n' << endl;

    for(int rep = 0; rep < sequences; ++rep){
        int sequence[sequenceLen];
        for (int &i : sequence) {
            i = rand()%numBank;
        }

        int page_faults = 0;
        int prev_page_faults = 1001;
        std::deque<int> memory;

        for(int frames = 1; frames < numFrames; ++frames){
            memory.clear();

            for (int i : sequence) {
                if(memory.size() < frames){
                    if(!contains(memory, i)){
                        memory.push_back(i);
                        ++page_faults;
                    }
                }

                if(memory.size() >= frames){
                    if(!contains(memory, i)){
                        memory.pop_front();
                        memory.push_back(i);
                        ++page_faults;
                    }
                }

            }

            if (page_faults > prev_page_faults){
                std::cout << "Anomaly Discovered! " << std::endl;
                std::cout << '\t' << "Sequence: " << rep << std::endl;
                std::cout << '\t' << "Page Faults: " << page_faults << " @ " << frames << " frames." << std::endl;
                std::cout << '\t' << "Page Faults: " << prev_page_faults << " @ " << (frames - 1) << " frames.\n";
                count++;
            }
            prev_page_faults = page_faults;
            page_faults = 0;
        }
    }
    std::cout << '\n' << "Anomaly detected " << count << " times." << std::endl;
    return 0;

}