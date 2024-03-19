#include <fstream>
#include <iostream>
#include <vector>

/*
 * <more_to_read>
 *
 *the function checks if there is any more strings in the file to read.
 *
 * input: std::ifstream &file
 * output: return a bool value. if there is more to read in the file it returns true and 
 * false if there is nothing to read.
 */
bool more_to_read(std::ifstream &file) {
  file >> std::noskipws;
  while (file.peek() == ' ') {
    char discard;
    file >> discard;
  }
  return !(file.eof() || std::iscntrl(file.peek()));
}

/*
 * <counter_function>
 *
 * the function gets three string vectors and it checks to see if there are any words in fixme_words that match a word in typo_words.
 * then if there are any wrong words found, the function replaces the misspelled word with the correct version from fixo_words vector.
 * And it counts that correction. 
 *
 * input: three string vectors named fixme_words, typo_words, and fixo_words.
 * output: it returns an integer called counter
 */
int counter_function(std::vector<std::string> &fixme_words, std::vector<std::string> &typo_words, std::vector<std::string> &fixo_words) {
    int counter = 0;
    for (int fixme_index = 0; fixme_index < fixme_words.size(); fixme_index++) {
        for (int typo_index = 0; typo_index < typo_words.size(); typo_index++) {
            if (fixme_words[fixme_index] == typo_words[typo_index]) {
                fixme_words[fixme_index] = fixo_words[typo_index];
                counter++;
            }
        }
    }
    return counter;
}

/*
 * writer_function
 *
 * The function uses a for loop to go through every element of fixme_words vector. then it starts adding all the elements to fixed_sentence
 * with a space in between them and a period at the end.
 *
 * input: one string vector called fixme_words and one string called fixed_sentence
 * output: the function does not return anything. The output is a sentence.
 */
void writer_function(std::vector<std::string>& fixme_words, std::string& fixed_sentence) {
    for (int fixme_index = 0; fixme_index < fixme_words.size(); fixme_index++) {
        if (fixed_sentence == "") {
            fixed_sentence = fixme_words[fixme_index];
        }
        else {
            fixed_sentence += " " + fixme_words[fixme_index];
        }
        if (fixme_index == fixme_words.size() - 1) {
            fixed_sentence += ".";
        }
    }
}


/*
 * <fcc>
 *
 * Reads in the input from the fixos file and the typos file.
 * Correlates the lists of typos and fixos.
 * Guarantees that the list of typos and fixos have the same number of entries.
 * Read in the sentence to fix from the fixme file.
 * calles the function counter to Iterate through the words in the sentence to fix and, for each,
 * determine whether the word needs to be fixed; and if so, find and make the appropriate replacement.
 * calles the function writer_function to format and add everything to fixed_sentence.
 *
 * input: three constant strings called fixme_filename, typo_filename, and fixo_filename. one string called fixed_sentence
 * output: returns -1 if there are more elements in fixo_file than typo_file, returns the counter number after calling the function.Has the fixed_sentence after calling the
 * writer_function.
 */
int fcc(const std::string &fixme_filename, const std::string &typo_filename,
        const std::string &fixo_filename, std::string &fixed_sentence) {

    std::string word{};

    std::ifstream fixme_file;
    std::ifstream typo_file;
    std::ifstream fixo_file;
    fixme_file.open(fixme_filename);
    typo_file.open(typo_filename);
    fixo_file.open(fixo_filename);

    std::vector<std::string> fixo_words{};
    std::vector<std::string> typo_words{};

    while (more_to_read(fixo_file)&&more_to_read(typo_file)) {
        fixo_file >> word;
        fixo_words.push_back(word);

        typo_file >> word;
        typo_words.push_back(word);
    }
    if (more_to_read(fixo_file) || more_to_read(typo_file)) {
        return -1;
    }

    std::vector<std::string> fixme_words{};

    while (more_to_read(fixme_file)) {
        fixme_file >> word;
        fixme_words.push_back(word);
    }

    int counter = counter_function(fixme_words, typo_words, fixo_words);
        
    writer_function(fixme_words, fixed_sentence);

  return counter;
}
