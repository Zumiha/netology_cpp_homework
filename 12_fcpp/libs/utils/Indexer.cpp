#include "Indexer.h"

#include <boost/algorithm/string.hpp>
#include <cctype>
#include <sstream>
#include <algorithm>

TextIndexer::TextIndexer() {
    // Инициализируем Boost.Locale в UTF-8
    gen_.locale_cache_enabled(true);
    loc_ = gen_.generate("en_US.UTF-8");
    std::locale::global(loc_);
}

void TextIndexer::indexContent(const std::string& content) {
    if (content.empty()) {
        return;
    }    
    std::string lowercase_content = boost::locale::to_lower(content, loc_); // Перевод всего в нижний регистр с помощью Boost.Locale
    extractAndCountWords(lowercase_content);    // Обработка и подсчет слов
}

void TextIndexer::clear() {
    word_frequencies_.clear();
}

std::vector<TextIndexer::WordFrequency> TextIndexer::getWordFrequencies() const {
    std::vector<WordFrequency> result;
    result.reserve(word_frequencies_.size());
    
    for (const auto& pair : word_frequencies_) {
        result.emplace_back(pair.first, pair.second);
    }
    
    return result;
}

std::vector<TextIndexer::WordFrequency> TextIndexer::getWordFrequenciesSorted() const {
    auto result = getWordFrequencies();
    
    std::sort(result.begin(), result.end(), 
              [](const WordFrequency& a, const WordFrequency& b) {
                  return a.frequency > b.frequency;
              });
    
    return result;
}

size_t TextIndexer::getUniqueWordCount() const {
    return word_frequencies_.size();
}

size_t TextIndexer::getTotalWordCount() const {
    size_t total = 0;
    for (const auto& pair : word_frequencies_) {
        total += pair.second;
    }
    return total;
}

size_t TextIndexer::getWordFrequency(const std::string& word) const {
    std::string lowercase_word = boost::locale::to_lower(word, loc_);
    auto it = word_frequencies_.find(lowercase_word);
    return (it != word_frequencies_.end()) ? it->second : 0;
}

std::string TextIndexer::prepareSqlInsertStatement(const std::string& table_name) const {
    std::ostringstream oss;
    oss << "INSERT INTO " << table_name << " (word, frequency) VALUES ";
    
    bool first = true;
    for (const auto& pair : word_frequencies_) {
        if (!first) oss << ", ";
        oss << "('" << escapeSqlString(pair.first) << "', " << pair.second << ")";
        first = false;
    }
    oss << ";";
    
    return oss.str();
}

std::vector<std::pair<std::string, size_t>> TextIndexer::getSqlParameterPairs() const {
    std::vector<std::pair<std::string, size_t>> result;
    result.reserve(word_frequencies_.size());
    
    for (const auto& pair : word_frequencies_) {
        result.emplace_back(pair.first, pair.second);
    }
    
    return result;
}

void TextIndexer::extractAndCountWords(const std::string& content) {
    std::string current_word;
    current_word.reserve(MAX_WORD_LENGTH + 1);
    
    for (char c : content) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            current_word += c;
        } else {
            if (!current_word.empty()) {
                processWord(current_word);
                current_word.clear();
            }
        }
    }
    
    // Обрабатываем последнее слово если нет никакого разделителя
    if (!current_word.empty()) {
        processWord(current_word);
    }
}

void TextIndexer::processWord(const std::string& word) {
    if (word.length() >= MIN_WORD_LENGTH && word.length() <= MAX_WORD_LENGTH) {
        ++word_frequencies_[word];
    }
}

std::string TextIndexer::escapeSqlString(const std::string& str) const {
    std::string escaped;
    escaped.reserve(str.length() * 2);
    
    for (char c : str) {
        if (c == '\'') {
            escaped += "''";
        } else {
            escaped += c;
        }
    }
    
    return escaped;
}
