#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class HtmlElement
{
    friend class HtmlBuilder;
    std::string name, text;
    std::vector<HtmlElement> elements;

    const int indent_size = 2;

    HtmlElement() {}

    HtmlElement(const std::string& name, const std::string& text)
        : name(name)
        , text(text)
    {}

public:
    std::string str(int indent = 0) const
    {
        std::ostringstream oss;
        std::string i(indent_size*indent, ' ');
        oss << i << "<" << name << ">" << std::endl;
        if(text.size() > 0)
            oss << std::string(indent_size*(indent + 1), ' ') << text << std::endl;

        for(const auto& e : elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << std::endl;
        return oss.str();
    }
};

class HtmlBuilder
{
    HtmlElement root;

public:
    HtmlBuilder(std::string root_name)
    {
        root.name = root_name;
    }

    HtmlBuilder& add_child(std::string child_name, std::string child_text)
    {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    std::string str() const
    {
        return root.str();
    }

    HtmlElement build()
    {
        return root;
    }
};

int main()
{
    HtmlElement html = HtmlBuilder("ul").add_child("li", "hello").add_child("li", "world").build();
    std::cout<< html.str() << std::endl;
    return 0;
}
