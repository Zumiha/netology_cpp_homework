#include <fstream>

class Printable
{
public:
    virtual ~Printable() = default;

    virtual std::string printAsHTML() const = 0;
    virtual std::string printAsText() const = 0;
    virtual std::string printAsJSON() const = 0;
};

/*=========================================================
в классе Printable нарушается принцип открытости/закрытости. 
для расширения поведения придутся вносить в изменения в код 
==========================================================*/

class Data : public Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    std::string printAsHTML() const override
    {
        if (format_ != Format::kHTML) {
            throw std::runtime_error("Invalid format!");
        }
        return "<html>" + data_ + "<html/>";
    }
    std::string printAsText() const override
    {
        if (format_ != Format::kText) {
            throw std::runtime_error("Invalid format!");
        }
        return data_;
    }
    std::string printAsJSON() const override
    {
        if (format_ != Format::kJSON) {
            throw std::runtime_error("Invalid format!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
    Format format_;
};

/*=========================================================
не выполняется принцип подстановки Лисковой. есть возможность 
совпадения факторов, которые приведут к вызову исключения

не выполняется принцип разделеня интерфейса (в 
результате получаем "толстый интерфейс"), методы не 
специализированны и разработано всё для множество задач
косвенно это так же закрытвает расширение и требует изменений
в результате расширения

так же класс Data ответственнен за предствление данных в 
нескольких форматах
==========================================================*/

void saveTo(std::ofstream &file, const Printable& printable, Data::Format format)
{
    switch (format)
    {
    case Data::Format::kText:
        file << printable.printAsText();
        break;
    case Data::Format::kJSON:
        file << printable.printAsJSON();
        break;
    case Data::Format::kHTML:
        file << printable.printAsHTML();
        break;
    }
}

/*=========================================================
не выполняется принцип разделеня интерфейса (в 
результате получаем "толстый интерфейс"), методы не 
специализированны и разработано всё для множество задач
косвенно это так же закрытвает расширение и требует изменений
в результате расширения
==========================================================*/

void saveToAsHTML(std::ofstream &file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kHTML);
}

void saveToAsJSON(std::ofstream &file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kJSON);
}

void saveToAsText(std::ofstream &file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kText);
}