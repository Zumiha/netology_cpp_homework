#include "textdecor.h"

int main() {
    auto text_block = new ItalicText(new BoldText(new Text()));
    text_block->render("Hello world");
    std::cout << "\n\n";
    auto text_block1 = new Paragraph(new Text());
    text_block1->render("Hello world");
    std::cout << "\n\n";
    auto text_block2 = new Reversed(new Text());
    text_block2->render("Hello world");
    std::cout << "\n\n";
    auto text_block3 = new Link(new Text());
    text_block3->render("netology.ru","Hello world");
    std::cout << "\n\n";

    return 0;
}