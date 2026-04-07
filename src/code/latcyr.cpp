#include <unicode.hpp>
#include <latcyr.hpp>
#include <unordered_set>
#include <cwctype>

const std::unordered_set<int32_t> LATIN_CHAR_POOL{
    'A', 'a',
    'B', 'b',
    'C', 'c',
    'Ć', 'ć',
    'Č', 'č',
    'D', 'd',
    'E', 'e',
    'F', 'f',
    'G', 'g',
    'H', 'h',
    'I', 'i',
    'J', 'j',
    'K', 'k',
    'L', 'l',
    'Ł', 'ł',
    'M', 'm',
    'N', 'n',
    'Ń', 'ń',
    'O', 'o',
    'P', 'p',
    'R', 'r',
    'S', 's',
    'Ś', 'ś',
    'Š', 'š',
    'T', 't',
    'U', 'u',
    'Ŭ', 'ŭ',
    'V', 'v',
    'Y', 'y',
    'Z', 'z',
    'Ź', 'ź',
    'Ž', 'ž',
    'Ĺ', 'ĺ',
    'W', 'w',
};

std::unordered_set<int32_t> HUKI_HAL {
    'A', 'a',
    'O', 'o',
    'U', 'u',
    'E', 'e',
    'I', 'i',
    'Y', 'y'
};

utf8str translateLatCyr(utf8str str) {
    utf8str out{};
    for (size_t i = 0; i < str.size(); i++) {
        switch (static_cast<int>(str[i])) {
            case 'A':
                if (i > 0 && (str[i - 1] == 'L' || str[i - 1] == 'l'))
                    out.push_back('Я');
                else if (i > 0 && (str[i - 1] == 'I' || str[i - 1] == 'i' || str[i - 1] == 'J' || str[i - 1] == 'j'))
                    out.push_back('Я');                    
                else
                    out.push_back('А');
                break;
            case 'a':
                if (i > 0 && (str[i - 1] == 'L' || str[i - 1] == 'l'))
                    out.push_back('я');
                else if (i > 0 && (str[i - 1] == 'I' || str[i - 1] == 'J'))
                    out.push_back('Я');
                else if (i > 0 && (str[i - 1] == 'i' || str[i - 1] == 'j'))
                    out.push_back('я');
                else
                    out.push_back('а');
                break;
            case 'B':
                out.push_back('Б');
                break;
            case 'b':
                out.push_back('б');
                break;
            case 'C':
                if (i < str.size() - 1 && (str[i + 1] == 'H' || str[i + 1] == 'h')) {
                    str.erase(i + 1);
                    out.push_back('Х');
                } else
                    out.push_back('Ц');
                break;
            case 'c':
                if (i < str.size() - 1 && (str[i + 1] == 'H' || str[i + 1] == 'h')) {
                    str.erase(i + 1);
                    out.push_back('х');
                } else
                    out.push_back('ц');
                break;
            case 'Ć':
                if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                    out.append("Ць");
                else
                    out.append("ЦЬ");
                break;
            case 'ć':
                out.append("ць");
                break;
            case 'Č':
                out.push_back('Ч');
                break;
            case 'č':
                out.push_back('ч');
                break;
            case 'D':
                out.push_back('Д');
                break;
            case 'd':
                out.push_back('д');
                break;
            case 'E':
                if (i > 0 && (str[i - 1] == 'L' || str[i - 1] == 'l'))
                    out.push_back('Е');
                else if (i > 0 && (str[i - 1] == 'I' || str[i - 1] == 'i' || str[i - 1] == 'J' || str[i - 1] == 'j'))
                    out.push_back('Е');                    
                else
                    out.push_back('Э');
                break;
            case 'e':
                if (i > 0 && (str[i - 1] == 'L' || str[i - 1] == 'l'))
                    out.push_back('е');
                else if (i > 0 && (str[i - 1] == 'I' || str[i - 1] == 'J'))
                    out.push_back('Е');
                else if (i > 0 && (str[i - 1] == 'i' || str[i - 1] == 'j'))
                    out.push_back('е');
                else
                    out.push_back('э');
                break;
            case 'F':
                out.push_back('Ф');
                break;
            case 'f':
                out.push_back('ф');
                break;
            case 'G':
                out.push_back('Ґ');
                break;
            case 'g':
                out.push_back('ґ');
                break;
            case 'H':
                out.push_back('Г');
                break;
            case 'h':
                out.push_back('г');
                break;
            case 'I':
                if (!(i < str.size() - 1 && HUKI_HAL.contains(str[i + 1])))
                    out.push_back('І');
                break;
            case 'i':
                if (!(i < str.size() - 1 && HUKI_HAL.contains(str[i + 1])))
                    out.push_back('і');
                break;
            case 'J':
                if (!(i < str.size() - 1 && HUKI_HAL.contains(str[i + 1])))
                    out.push_back('Й');
                else if (i == 0 || (i > 0 && (HUKI_HAL.contains(str[i - 1]) || std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                    break;
                else
                    out.push_back('\'');
                break;
            case 'j':
                if (!(i < str.size() - 1 && HUKI_HAL.contains(str[i + 1])))
                    out.push_back('й');
                else if (i == 0 || (i > 0 && (HUKI_HAL.contains(str[i - 1]) || std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                    break;
                else
                    out.push_back('\'');
                break;
            case 'K':
                out.push_back('К');
                break;
            case 'k':
                out.push_back('к');
                break;
            case 'L':
                if (i < str.size() - 1 && HUKI_HAL.contains(str[i + 1]))
                    out.push_back('Л');
                else if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                    out.append("Ль");
                else
                    out.append("ЛЬ");
                break;
            case 'l':
                if (i < str.size() - 1 && HUKI_HAL.contains(str[i + 1]))
                    out.push_back('л');
                else
                    out.append("ль");
                break;
            case 'Ĺ':
                if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                    out.append("Ль");
                else
                    out.append("ЛЬ");
                break;
            case 'ĺ':
                out.append("ль");
                break;
            case 'Ł':
                out.push_back('Л');
                break;
            case 'ł':
                out.push_back('л');
                break;
            case 'M':
                out.push_back('М');
                break;
            case 'm':
                out.push_back('м');
                break;
            case 'N':
                out.push_back('Н');
                break;
            case 'n':
                out.push_back('н');
                break;
            case 'Ń':
                if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                    out.append("Нь");
                else
                    out.append("НЬ");
                break;
            case 'ń':
                out.append("нь");
                break;
            case 'O':
                if (i > 0 && (str[i - 1] == 'L' || str[i - 1] == 'l'))
                    out.push_back('Ё');
                else if (i > 0 && (str[i - 1] == 'I' || str[i - 1] == 'i' || str[i - 1] == 'J' || str[i - 1] == 'j'))
                    out.push_back('Ё');                    
                else
                    out.push_back('О');
                break;
            case 'o':
                if (i > 0 && (str[i - 1] == 'L' || str[i - 1] == 'l'))
                    out.push_back('ё');
                else if (i > 0 && (str[i - 1] == 'I' || str[i - 1] == 'J'))
                    out.push_back('Ё');
                else if (i > 0 && (str[i - 1] == 'i' || str[i - 1] == 'j'))
                    out.push_back('ё');
                else
                    out.push_back('о');
                break;
            case 'P':
                out.push_back('П');
                break;
            case 'p':
                out.push_back('п');
                break;
            case 'R':
                out.push_back('Р');
                break;
            case 'r':
                out.push_back('р');
                break;
            case 'S':
                out.push_back('С');
                break;
            case 's':
                out.push_back('с');
                break;
            case 'Ś':
                if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                    out.append("Сь");
                else
                    out.append("СЬ");
                break;
            case 'ś':
                out.append("сь");
                break;
            case 'Š':
                out.push_back('Ш');
                break;
            case 'š':
                out.push_back('ш');
                break;
            case 'T':
                out.push_back('Т');
                break;
            case 't':
                out.push_back('т');
                break;
            case 'U':
                if (i > 0 && (str[i - 1] == 'L' || str[i - 1] == 'l'))
                    out.push_back('Ю');
                else if (i > 0 && (str[i - 1] == 'I' || str[i - 1] == 'i' || str[i - 1] == 'J' || str[i - 1] == 'j'))
                    out.push_back('Ю');                    
                else
                    out.push_back('У');
                break;
            case 'u':
                if (i > 0 && (str[i - 1] == 'L' || str[i - 1] == 'l'))
                    out.push_back('ю');
                else if (i > 0 && (str[i - 1] == 'I' || str[i - 1] == 'J'))
                    out.push_back('Ю');
                else if (i > 0 && (str[i - 1] == 'i' || str[i - 1] == 'j'))
                    out.push_back('ю');
                else
                    out.push_back('у');
                break;
            case 'Ŭ':
                out.push_back('Ў');
                break;
            case 'ŭ':
                out.push_back('ў');
                break;
            case 'V':
                out.push_back('В');
                break;
            case 'v':
                out.push_back('в');
                break;
            case 'W':
                out.push_back('В');
                break;
            case 'w':
                out.push_back('в');
                break;
            case 'Y':
                out.push_back('Ы');
                break;
            case 'y':
                out.push_back('ы');
                break;
            case 'Z':
                out.push_back('З');
                break;
            case 'z':
                out.push_back('з');
                break;
            case 'Ź':
                if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                    out.append("Зь");
                else
                    out.append("ЗЬ");
                break;
            case 'ź':
                out.append("зь");
                break;
            case 'Ž':
                out.push_back('Ж');
                break;
            case 'ž':
                out.push_back('ж');
                break;
            default:
                out.push_back(str[i]);
                break;
        }
    }
    return out;
}