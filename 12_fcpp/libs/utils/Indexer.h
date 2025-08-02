#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <boost/locale.hpp>

class TextIndexer {
public:
    struct WordFrequency {
        std::string word;
        size_t frequency;
        
        WordFrequency(const std::string& w, size_t f) : word(w), frequency(f) {};
    };

private:
    std::unordered_map<std::string, size_t> word_frequencies_;
    boost::locale::generator gen_;
    std::locale loc_;
    
    static constexpr size_t MIN_WORD_LENGTH = 3;
    static constexpr size_t MAX_WORD_LENGTH = 32;

public:
    TextIndexer();

    // Основная функция индексирования
    void indexContent(const std::string& content);
    void clear(); // Очищение всех данных из word_frequencies_


    std::vector<WordFrequency> getWordFrequencies() const; // Слова из word_frequencies_ подготавливаются в вектор
    std::vector<WordFrequency> getWordFrequenciesSorted() const; // Сортировка слов в векторе

    // Для статистики
    size_t getUniqueWordCount() const; // Кол-во уникальных слов
    size_t getTotalWordCount() const; // Всего слов обработано
    size_t getWordFrequency(const std::string& word) const; // Кол-во определенного слова

    std::string prepareSqlInsertStatement(const std::string& table_name = "word_frequencies") const;    // Подготовка SQL-запроса
    std::vector<std::pair<std::string, size_t>> getSqlParameterPairs() const;   // Подготовка вставки для параметризованных запросов

private:
    void extractAndCountWords(const std::string& content);      // Обработка и подсчет слов из indexContent()
    void processWord(const std::string& word);                  // Добавление обработанного слова в word_frequencies_
    std::string escapeSqlString(const std::string& str) const;
};