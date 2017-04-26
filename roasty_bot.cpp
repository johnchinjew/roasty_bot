/* ===========================================================================

  Title: ROASTY_BOT — The JARBCO rap generator.
  Description: A JARBCO C++ project for COMSC-110-1335.
  Authors: Brandon Chan, John Chin-Jew, & Anthony Saikali.
  Date: Spring, 2017

  APIs: Data Muse (http://datamuse.com)
  Libraries: C++ Requests (github.com/whoshuu/cpr)

=========================================================================== */

/* ===========================================================================

  DEPENDENCIES

=========================================================================== */

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>

#include <cpr/cpr.h>

/* ===========================================================================

  SCOPING

=========================================================================== */

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

using cpr::Get;
using cpr::Url;

/* ===========================================================================

  FORWARD DECLARATIONS

=========================================================================== */

int rand_range(const int, const int);
vector<string> split(const string, const char delimiter=' ');
string lower_all(const string s);
string trim_end_space(const string s);
string strip_punc(const string s);
void slow_print(const string, const bool end=true, const int rate=35,
                const int pause=150);
void clear();
string extract_last_word(const string);
string format_sentence(const string s);
string make_line(const vector<string>, const vector<string>);
vector<string> get_rhymes(const string);

/* ===========================================================================

  MAIN

=========================================================================== */

int main() {
  vector<string> lines = {
    "Come from the west side, spitting some _.",
    "Got a fity under my arm and you got _.",
    "I'm ten times better than you, you ain't _.",
    "Chillin' relaxin', acting like a _.",
    "It's funny to me, you're nothing but a _!",
    "Got _ and _ all day... call me _.",
    "For my brotha Ryan, 6 feet under _.",
    "What are you? I'm a _ born and raised.",
    "Catch me later, I be kickin' _ by the _.",
    "Hah, what? You think this all a _?",
    "Jus' here shootin some _ outside of the _.",
    "Cruisin' down the street in my ultra _.",
    "Literally, nothing can stop my super _.",
    "You tryna be that _, but you only be a _.",
    "We're JARBCO, kicking _ and chewing _."
  };

  clear();
  cout << "+ —— —— —— —— —— —— —— —— —— +\n";
  cout << "| I am ROASTY_BOT.           |\n";
  cout << "| The JARBCO rap generator.  |\n";
  cout << "| Enter 'Q' to quit.         |\n";
  cout << "+ —— —— —— —— —— —— —— —— —— +\n";

  string prompt_msg = "\nGive me a line: ";

  while (true) {
    string first_line, word_to_rhyme;
    vector<string> rhymes;

    do {
      slow_print(prompt_msg, false);
      getline(cin, first_line);
      if (lower_all(first_line) == "q") {
        slow_print("Quitting...", false);
        sleep_for(milliseconds(800));
        cout << endl;
        return 0;
      }
      word_to_rhyme = extract_last_word(first_line);
      rhymes = get_rhymes(word_to_rhyme);
      prompt_msg = "Try something else: ";
    } while (rhymes.size() < 10 || first_line.length() < 15);

    slow_print("\nGenerating rhymes...", true, 35, 400);
    slow_print("Mixing tapes...", true, 35, 400);
    slow_print("Summoning fire...", true, 35, 1500);

    clear();
    cout << "+ —— —— —— —— —— —— —— —— —— +\n";
    cout << "| I am ROASTY_BOT.           |\n";
    cout << "| The JARBCO rap generator.  |\n";
    cout << "| Enter 'Q' to quit.         |\n";
    cout << "+ —— —— —— —— —— —— —— —— —— +\n";

    slow_print("\n"+format_sentence(first_line));
    for (int i = 0; i < 8; i++) slow_print(make_line(lines, rhymes));

    prompt_msg = "\nGive me another line: ";
  }

  return 0;
}

/* ===========================================================================

  UTILITY FUNCTIONS

=========================================================================== */

// Returns random int w/in range [@min, @max] inclusive.
int rand_range(const int min, const int max) {
	static bool once = true;
  if (once) {
  	srand(time(0));
  	once = false;
  }
	return min+(rand()%(max-min+1));
}

// Returns a vector holding string @s split by @delimiter.
vector<string> split(const string s, const char delimiter) {
  vector<string> chunks;
  stringstream ss(s);
  string tok;
  while(getline(ss, tok, delimiter)) chunks.push_back(tok);
  return chunks;
}

// Returns string @s as lowercased string.
string lower_all(const string s) {
  string _s = s;
  for (int i = 0; i < _s.length(); i++) _s[i] = tolower(_s[i]);
  return _s;
}

// Returns string @s with all ending whitespace trimmed.
string trim_end_space(const string s) {
  string _s = s;
  int end = _s.find_last_not_of(" \t");
  if(string::npos != end) _s = _s.substr( 0, end+1 );
  return _s;
}

// Returns string @s with all punctuation removed.
string strip_punc(const string s) {
  string _s = s;
  for (int i = 0, len = _s.size(); i < len; i++) {
    if (ispunct(_s[i])) {
      _s.erase(i--, 1);
      len = _s.size();
    }
  }
  return _s;
}

// Slow prints @msg w/ typewriter effect.
void slow_print(const string s, const bool end, const int rate,
                const int pause) {
  for (int i = 0; i < s.length(); i++) {
    sleep_for(milliseconds(rate));
    cout << s[i] << flush;
  }
  sleep_for(milliseconds(pause));
  if (end) cout << endl;
  else cout << flush;
}

// Clears terminal output.
// Should work for Windows and Mac OS, but has fallback.
void clear() {
  #ifdef _WIN32
    system("cls");
  #elif __APPLE__ && __MACH__
    system("clear");
  #else
    for (int i = 0; i < 40; i++) cout << "\n";
    cout << flush;
  #endif
}

/* ===========================================================================

  CUSTOM FUNCTIONS

=========================================================================== */

// Returns the last word from string @s.
// Strips any excess punctuation, whitespace, or capitalization.
string extract_last_word(const string s) {
  return strip_punc(lower_all(split(trim_end_space(s)).back()));
}

// Returns string @s properly formatted with capitalization & punctuation.
string format_sentence(const string s) {
  string _s = trim_end_space(s);
  string punc = "!—-:;,.?";
  _s[0] = toupper(_s[0]);
  for (int i = 0; i < punc.length(); i++)
    if (_s[_s.length()-1] == punc[i]) return _s;
  return _s + ".";
}

// Returns random rap line populated with random rhymes.
// Replaces all '_' w/in random line from @line w/ random word from @words.
string make_line(const vector<string> lines, const vector<string> rhymes) {
  string l = lines[rand_range(0, lines.size()-1)];
	for (int i = 0; i < l.length(); i++)
		if (l[i] == '_')
      l.replace(l.find('_', i), 1, rhymes[rand_range(0, rhymes.size()-1)]);
	return l;
}

// Returns vector of rhymes for a given word @keyword.
// Sends a get request to api.datamuse.com, and processes response.
// Also uses the C++ Requests library (github.com/whoshuu/cpr).
vector<string> get_rhymes(const string keyword) {
  vector<string> rhymes;
  auto r = Get(Url{ "https://api.datamuse.com/words?rel_rhy="+keyword });
  if (r.status_code != 200) {
    cout << "Error! Problem getting rhymes from server." << endl;
  } else {
    string raw_rhymes = r.text;
    if (raw_rhymes.length() <= 2) return rhymes;
    int pos = 0;
    while (true) {
      int start = raw_rhymes.find("{\"word\":\"", pos)+9;
      if (start-9 < 0) break;
      int end = raw_rhymes.find('\"', start+1);
      rhymes.push_back(raw_rhymes.substr(start, end-start));
      pos = end+1;
    }
  }
  return rhymes;
}
