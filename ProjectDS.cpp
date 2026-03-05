#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

/* ΑΜ: 3212024246 Σπυρίδων Χόβολος
   ΑΜ: 3212024248 Γεώργιος Χουρδάς */

class Song{
private:
    int id;
    string title;
    string artist;
    int duration;
    int plays;

public:
    Song(){ // Default constructor
        id = -1;
        title = "";
        artist = "";
        duration = 0;
        plays = 0;
    };
    Song(int pid, string ptitle, string partist, int pduration) // Constructor για την εισαγωγή απο την χρήστη
    {
        id = pid;
        title = ptitle;
        artist = partist;
        duration = pduration;
        plays = 0;
    }
    Song(int pid, string ptitle, string partist, int pduration, int pplays) // Constructor για την εισαγωγή απο αρχείο
    {
        id = pid;
        title = ptitle;
        artist = partist;
        duration = pduration;
        plays = pplays;
    }

    // Αυξάνει τον μετρητή αναπαραγωγών κατά 1
    void increasePlays(){
        plays = plays + 1;
    }
    int getDuration(){ 
        return duration;
    }
    string getTitle(){ 
        return title; 
    }
    string getArtist(){ 
        return artist; 
    }
    
    int getID(){
        return id;
    }

    //Αυξάνει τον μετρητή αναπαραγωγών κατά 1
    int getPlays() { 
        return plays; 
    }

    //Εμφανίζει όλες τις πληροφορίες του τραγουδιού
    void showInfo(){
        int mins = duration /60;
        int secs = duration % 60; 
        cout << "Song ID: " << id << endl << "Title: " << title << endl << "Artist: " << artist << endl << "Duration: " << mins << ":" << secs << endl;
        cout << "Times played: " << plays << endl;
    }
};



struct Node{
    Song song;
    Node* next;
    Node* prev;
    Node(Song s):song(s), next(nullptr), prev(nullptr) {}
};

typedef struct {
 Node* head; // Δείκτης στην αρχή της λίστας
 Node* tail; // Δείκτης στο τέλος της λίστας
 Node* lastPlayed; // Το τελευταίο τραγούδι που παίχτηκε
 Node* current; // Δείκτης στο τρέχον τραγούδι που παίζει
 int size; // Πλήθος τραγουδιών στην playlist
} Playlist;

class HistoryStack{

    Song songs[15];
    int top; //Ελέγχει αν το stack είναι άδειο

    public:

        HistoryStack(){
            top = -1;
        }

        int getSize(){
            return top +1;
        }

        //Ελέγχει αν το stack είναι άδειο
        bool isEmpty(){
            if(top == -1){
                return true;
            }
            else{
                return false;
            }
        };
        //Ελέγχει αν το stack είναι γεμάτο
        bool isFull(){
            if (top == 14){
                return true;
            }else{
                return false;
            }
        };
        void pushHistory(const Song& song){
            
            if(isFull() == true){         //Σε περιπτωση που ο πινακας ειναι γεματος, ολα τα στοιχεια πανε μια θεση πισω, 
                for (int i = 0;i<14;i++){ //συνεπως το τελευταιο στοιχειο χανεται για να προστεθει το πιο προσφατο
                    songs[i] = songs[i+1];
                }
                songs[14] = song;
            }else{
                top++;
                songs[top] = song;
                
            }
        }
        //Εμφανίζει το ιστορικό τραγουδιών
        void displayHistory(){
            if(isEmpty() == true){
                cout << "History is empty." << endl;
            }
            else{
                for (int i = top; i>=0; i--){
                    cout << top - i +1 << ". ";
                    songs[i].showInfo();
                    cout << endl;
                }
            }
        }
        //Καθαρίζει το ιστορικό
        void clearHistory(){
            top = -1;
            cout << "History cleared" << endl;
        }
        Song recoverAndRewind(int userChoice){
            int realIndex = top - (userChoice - 1);
            top = realIndex;

            return songs[top];
        }
    };


class MusicPlaylist{
    private:
        Playlist pl;
        HistoryStack hs;
    public:
        MusicPlaylist(){
            pl.head = nullptr;
            pl.tail = nullptr;
            pl.lastPlayed = nullptr;
            pl.current = nullptr;
            pl.size = 0;
    }
    
    bool isEmpty(){
        return pl.size == 0;
    }
    //Προσθέτει τραγούδι στο τέλος της playlist
    void addSong(Song song){
        Node* newNode = new Node(song);
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if(pl.head == nullptr){
            pl.current = newNode;
            pl.head = newNode;
            pl.tail = newNode;

        }else {
            pl.tail->next = newNode;
            newNode->prev = pl.tail;
            pl.tail = newNode;
        }
        pl.size++;
    }
    //Υπολογίζει τη συνολική διάρκεια της playlist
    void getTotalDuration(){
        if (pl.head == nullptr){
            return;
        }

        Node* temp = pl.head;
        int total = 0;

        while(temp != nullptr){
            total += temp->song.getDuration();
            temp = temp->next;
        }
        int mins = total /60;
        int secs = total % 60;
        cout << "Total duration: " << " [" << mins << ":" << setw(2) << setfill('0') << secs << "]" << endl; 

    }
    //Εμφανίζει όλα τα τραγούδια της playlist
    void displayPlaylist(){
        if(pl.size == 0){
            cout << "Playlist is empty." << endl;
            return;
        }
        Node* temp = pl.head;
        int index = 1;
        int totalDuration = 0;

        while(temp != nullptr){
            int duration = temp->song.getDuration();
            int mins = duration /60;
            int secs = duration % 60;

            cout << index << ". " << temp->song.getTitle() << " - " << temp->song.getArtist() << " [" << mins << ":" << setw(2) << setfill('0') << secs << "]" << endl;
            totalDuration += duration;
            temp = temp->next;
            index++;
        }
            int mins = totalDuration /60;
            int secs = totalDuration % 60; ;
        cout << "Total songs: " << pl.size << endl << "Playlist duration: "<< "[" << mins << ":" << setw(2) << setfill('0') << secs << "]" << endl;
    }
    //Εμφανίζει πληροφορίες για το τραγούδι που παίζει αυτή τη στιγμή
    void displayCurrent(){
        if(pl.current == nullptr){
            cout << "No song is curently playing." << endl;
            return;
        }
        pl.current->song.showInfo();

    }
    //Αναζητά τραγούδι με βάση τον τίτλο
    Node* searchByTitle(const string& title){
        if(pl.head == nullptr){
            return NULL;
        }

        string key = string(title);
        Node* temp = pl.head;

        while(temp != nullptr){
            //αν βρέθηκε τοτε: 
            if(temp->song.getTitle() == key){
                return temp;

            }
            temp = temp->next;

        }
        //αν δεν βρέθηκε τοτε: 

        return NULL;
        
    }
    //Προσθέτει τραγούδι σε συγκεκριμένη θέση της playlist
    void addAt(Song song, int position){
        //Έλεγχος αν η θέση είναι έξω απο τα όρια
        if(position < 1 || position > pl.size +1){
            cout << "Invalid position." << endl;
            return;
        }

        Node* newNode= new Node(song);
        //1η περίπτωση: προσθήκη στην αρχή
        if(position == 1){
            newNode->prev = nullptr;
            newNode->next = pl.head;

            if(pl.head != nullptr){
                pl.head->prev = newNode;
            }
            else{
                pl.tail = newNode;
                pl.current = newNode;
            }

            pl.head = newNode;
            pl.size++;
            return;
        }
        //2η περίπτωση: προσθήκη στο τέλος
        if(position == pl.size +1){
            newNode->prev = pl.tail;

            if(pl.tail != nullptr){
                pl.tail->next = newNode;
            }
            pl.tail = newNode;

            //αν η λίστα είναι άδεια
            if(pl.size == 0){
                pl.head = newNode;
                
            }
            pl.size++;
        }
        //3η περίπτωση: προσθηκη στην μέση  
        Node* temp = pl.head;
        int index = 1;
        while(index < position -1){
            temp = temp->next;
            index++;
        }
        // temp δείχνει στον κόμβο πριν από τη θέση εισαγωγής
        newNode->next = temp->next;
        newNode->prev = temp;

        temp->next->prev = newNode;
        temp->next = newNode;

        pl.size++;

        
    }
    //Διαγράφει τραγούδι από συγκεκριμένη θέση
    void removeAt(int position){
        if(position < 1 || position > pl.size){
            cout << "Invalid position." << endl;
            return;
        }
        //1η περίπτωση: διαγραφή πρώτου κόμβου
        if(position == 1){
            Node* temp = pl.head;

            // Αν ήταν το μόνο τραγούδι στην playlist
            if(pl.head == pl.tail){
                pl.head = nullptr;
                pl.tail = nullptr;
                pl.current = nullptr;
        }else{
            pl.head = temp->next;
            pl.head->prev = nullptr;

            if(pl.current == temp){
                pl.current = pl.head;
            }
        }
        delete temp;
        pl.size--;
        return;
    }
        //2η περίπτωση : διαγραφή τελευταίου κόμβου 
        if(position == pl.size){
            Node* temp = pl.tail;

            pl.tail = temp->prev;
            pl.tail->next = nullptr;

            if(pl.current == temp){
                pl.current = pl.tail;
            }
            delete temp;
            pl.size--;
            return;

        }
        //3η περίπτωδη : διαγραφή απο την μέση
        Node* temp  = pl.head;
        int index = 1;

        while (index < position) {
            temp = temp->next;
            index++;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        
        if (pl.current == temp){
            pl.current = temp->next;
        }
        delete temp;
        pl.size--;


}
    //Πηαίνει στο επόμενο τραγούδι
    void nextSong(){
        
         if(pl.current == nullptr){
            cout << "No song is playing right now." << endl;
            return;
        }
        if(pl.current->next == nullptr){
            cout << "No songs left.";
            return;
        }

        pl.current = pl.current->next;
        play();
    }
    //πηγαίνει στο προηγούμενο τραγούδι
    void previousSong(){
        if(pl.current == nullptr){
            cout << "Playlist is empty." << endl;
            return;
        }else if(pl.current == pl.head){
            cout << "Already at the beginning of the playlist. " << endl;
            return;
        }
        pl.current = pl.current->prev;
        play();


    }
    //Αναζητά και εμφανίζει όλα τα τραγούδια συγκεκριμένου καλλιτέχνη
    void searchByArtist(const string& artist){
        if(pl.head == nullptr){
            cout << "Playlist is empty." << endl;
        }
        Node* temp = pl.head;
        bool found = false;

        cout << "Artist's songs:" << endl;

        while(temp != nullptr){
            if(temp->song.getArtist() == artist){
                temp->song.showInfo();
                cout <<endl;
                found = true;
            }
            temp = temp -> next;
        }
        if(!found){
            cout << "No songs by this artist were found." << endl;
        }
    }
    //Παίζει το τρέχον τραγούδι και το προσθέτει στο ιστορικό
    void play(){
        if(pl.current == nullptr){
            cout << "No song is currently selected" << endl;
            return;
        }
        cout << "Now playing: " << pl.current->song.getTitle() << "-" << pl.current->song.getArtist() << endl;

        pl.current->song.increasePlays();
        cout << endl;

         // Προσθήκη στο ιστορικό μόνο αν είναι άλλο τραγούδι από το προηγούμενο
        if (pl.current != pl.lastPlayed) {
            hs.pushHistory(pl.current->song);
            pl.lastPlayed = pl.current;
        }
    }
    //Μετακινεί το current σε συγκεκριμένη θέση
    void goTo(int position){
        if(pl.size == 0){
            cout << "Playlist is empty." << endl;
            return;
        }
        if(position < 1 || position > pl.size){
            cout << "Invalid position.\n";
            return;
        }
        Node* temp = pl.head;
        int index = 1;

        while (index < position) {
            temp = temp->next;
            index++;
        }

        pl.current = temp;

        cout << "Moved to: " << temp->song.getTitle() << "-" << temp->song.getArtist() << endl;

    }

    void goBack(){
        if(hs.isEmpty()){
            cout << "History is empty." << endl;
            return;
        }

        cout << "Select a song from history to go back to:" << endl;
        hs.displayHistory();

        int choice;
        cout << "Choice: ";
        cin >> choice;

        if (choice < 1 || choice > hs.getSize()){
            cout << "Invalid choice." << endl;
            return;
        }

        Song targetSong = hs.recoverAndRewind(choice);

        Node* temp = pl.head;
        bool found = false;

        while (temp != nullptr){

            if(temp->song.getID() == targetSong.getID()){
                found = true;
                break;
            }
            temp = temp ->next;
        }

        if (found) {
            pl.current = temp;
            pl.lastPlayed = temp;

            cout << "Went back to: " << pl.current->song.getTitle()
            << " - " << pl.current->song.getArtist() << endl;
        } else {
            cout << "Song exists in history but was removed from the playlist." << endl;
        }
    }
    //Εμφανίζει το τραγούδι με τις περισσότερες αναπαραγωγές
    void displayPopularSong(){
        if(pl.size == 0){
            cout << "Playlist is empty." << endl;
            return;
        }
        Node* temp = pl.head;
        int maxPlays = 0;

        // 1η διαδρομή: Βρίσκω το μέγιστο plays
        while (temp != nullptr) {
            if (temp->song.getPlays() > maxPlays) {
                maxPlays = temp->song.getPlays();
            }

            temp = temp->next;
        }
        // 2η διαδρομή: Εμφανίζω ΟΛΑ τα τραγούδια με maxPlays
        cout << "Most popular song(s):" << endl;
        temp = pl.head;

         while (temp != nullptr) {
            if (temp->song.getPlays() == maxPlays) {

                int duration = temp->song.getDuration();
                int mins = duration / 60;
                int secs = duration % 60;

                cout << temp->song.getTitle() << " - " << temp->song.getArtist() << " (" << maxPlays << " plays) " << "[" << mins << ":" << setw(2) << setfill('0') << secs << "]" << endl;
        }

        temp = temp->next;
        }
    }
    void displayHistory(){
        hs.displayHistory();
    }

    void clearHistory(){
        hs.clearHistory();
    }
    //Αποθηκεύει την playlist σε αρχείο
    void saveToFile(const string& filename){
        ofstream file(filename);

        if(!file.is_open()){
            cout << "File failed to load." << endl;
            return;
        }

        Node* temp = pl.head;

        while(temp != nullptr){
            file << temp->song.getID()<< ","
            << temp->song.getTitle() << ","
            << temp->song.getArtist() << ","
            << temp->song.getDuration() << ","
            << temp->song.getPlays() << endl;
            temp = temp->next;
        }

        file.close();
        cout << "Saved in file: " << filename << endl;
    }
    //Φορτώνει τραγούδια από αρχείο και δημιουργεί νέα playlist
   void loadSongsFromFile(const string& filename){
        ifstream file(filename);

        if(!file.is_open()){
            cout << "File failed to load." << endl;
            return;
        }

        //Καθαρισμός παλιάς playlist
        Node* current = pl.head;
        while(current != nullptr){
            Node* next = current -> next;
            delete current;
            current = next;
        }

        pl.head = nullptr;
        pl.tail = nullptr;
        pl.current = nullptr;
        pl.lastPlayed = nullptr;
        pl.size = 0;

        //Ανάγνωση εγγράφου γραμμή γραμμή
        string line;
        while(getline(file,line)){
            if(line.empty()) continue;

            string sid, title, artist, sdur, splays;

            stringstream ss(line);
            getline(ss, sid, ',');
            getline(ss, title, ',');
            getline(ss, artist, ',');
            getline(ss, sdur, ',');
            getline(ss, splays, ',');

            if(sid.empty() || title.empty() || artist.empty() || sdur.empty() || splays.empty()){ // se periptosi xalasmenis gramis, thn prospername
                continue;
            }

            int id = stoi(sid);
            int duration = stoi(sdur);
            int plays = stoi(splays);

            Song s(id, title, artist, duration, plays);
            addSong(s);
        }

        file.close();

        if (pl.head != nullptr){
            pl.current = pl.head;
            cout << "Playlist loaded from file: " << filename << endl;
        }else{
            cout << "File was empty" << endl;
        }

    } 
};


int main(void){
    //Δημιουργία playlist
    MusicPlaylist mp;

    int choice;
    //Επανάληψη της λειτουργίας με while
    do{
        cout << "1. Play current song " << endl;
        cout << "2. Next song" << endl;
        cout << "3. Previous song" << endl;
        cout << "4. Go back to" << endl;
        cout << "5. Go to position" << endl;
        cout << "6. Display playlist" << endl;
        cout << "7. Add song" << endl;
        cout << "8. Delete song" << endl;
        cout << "9. Search song" << endl;
        cout << "10. Display history" << endl;
        cout << "11. Clear history" << endl;
        cout << "12. Statistics" << endl;
        cout << "13. Load from file" << endl;
        cout << "14. Save to file" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: " << endl; 

        cin >> choice;

        if(choice == 1){
            mp.play();
        }

        else if(choice == 2){
            mp.nextSong();
        }

        else if(choice == 3){
            mp.previousSong();
        }

        else if (choice == 4) {
            mp.goBack();
        }

        else if (choice == 5) {
            int pos;
            cout << "Position: ";
            cin >> pos;
            mp.goTo(pos);
        }

        else if (choice == 6) {
            mp.displayPlaylist();
        }
        else if (choice == 7) { //Συμπλήρωση στοιχείων τραγουδιού από τον χρήστη
            int id;
            int duration;
            int plays;
            string title;
            string artist;

            cout << "ID: "<< endl;
            cin >> id;

            cout << "Title: "<< endl;
            cin >> title;

            cout << "Artist: "<< endl;
            cin >> artist;

            cout << "Duration(in seconds): "<< endl;
            cin >> duration;
            
            Song s(id, title, artist, duration);
            mp.addSong(s);
        }

        else if (choice == 8) {
            int pos;
            cout << "Position: ";
            cin >> pos;
            mp.removeAt(pos);
        }

        else if (choice == 9) {
            int ichoice; //Μεταβλητή για επιλογή μεταξύ των 2 επιλογών παρακάτω
            cout << "Search by:" << endl;
            cout << "1. Artist" << endl << "2. Title" << endl;
            cin >> ichoice;

            if (ichoice == 1){
                string artist;
                cout << "Enter artist: ";
                cin >> artist;

                mp.searchByArtist(artist);
            } else if(ichoice == 2){
                string title;
                cout << "Enter title: ";
                cin >> title;

                Node* n = mp.searchByTitle(title);
                if (n == nullptr)
                    cout << "Not found.\n";
                else
                    n->song.showInfo();
            }else{
                cout << "Invalid choice" << endl;
            }
        }
        else if (choice == 10) {
            mp.displayHistory();
        }

        else if (choice == 11) {
            mp.clearHistory();
        }

        else if (choice == 12) {
            int ichoice;
            cout << "What would you like to see?" << endl;
            cout << "1. Display most popular song" << endl << "2. Get playlist's total duration" << endl;
            cout << "Choice: ";
            cin >> ichoice;

            if(ichoice == 1){
                mp.displayPopularSong();
            } 
            if(ichoice == 2) {
                mp.getTotalDuration();
            } 
            if(ichoice !=1 && ichoice !=2){
                cout << "Invalid choice" << endl;
            }
        }
        else if (choice == 13) {
            string filename;
            cout << "Filename: ";
            cin >> filename;
            mp.loadSongsFromFile(filename); // Αν τη φτιάξεις με όνομα αρχείου, άλλαξε το ανάλογα
        }

        else if (choice == 14) {
            string filename;
            cout << "Filename: ";
            cin >> filename;
            mp.saveToFile(filename);
        }
        
        cout << endl;
    }while(choice != 0);

    cout << "Program shutdown" << endl;

    return 0;
}