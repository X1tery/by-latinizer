#include <unicode.hpp>
#include <cyrlat.hpp>
#include <unordered_set>
#include <cwctype>

std::unordered_set<int32_t> CYRILLIC_CHAR_POOL{
    'А', 'а',
    'Б', 'б',
    'В', 'в',
    'Г', 'г',
    'Ґ', 'ґ',
    'Д', 'д',
    'Е', 'е',
    'Ё', 'ё',
    'Ж', 'ж',
    'З', 'з',
    'І', 'і',
    'I', 'i',
    'Й', 'й',
    'К', 'к',
    'Л', 'л',
    'М', 'м',
    'Н', 'н',
    'О', 'о',
    'П', 'п',
    'Р', 'р',
    'С', 'с',
    'Т', 'т',
    'У', 'у',
    'Ў', 'ў',
    'Ф', 'ф',
    'Х', 'х',
    'Ц', 'ц',
    'Ч', 'ч',
    'Ш', 'ш',
    'Ы', 'ы',
    'Ь', 'ь',
    'Э', 'э',
    'Ю', 'ю',
    'Я', 'я',
    '\'', '’'
};

std::unordered_set<int32_t> HAL_HUKI {
    'А', 'а',
    'Э', 'э',
    'О', 'о',
    'У', 'у',
    'Ў', 'ў',
    'Ы', 'ы',
    'Й', 'й',
    'І', 'і',
    'I', 'i',
    'Я', 'я',
    'Е', 'е',
    'Ё', 'ё',
    'Ю', 'ю',
    'Ь', 'ь',
    '\'', '’',
};

std::unordered_set<int32_t> NIEPIER_HUKI {
    'Р', 'р',
    'Ж', 'ж',
    'Ш', 'ш',
    'Ч', 'ч',
    'К', 'к'
};

std::unordered_set<int32_t> MIAK_HUKI {
    'Ь', 'ь',
    'І', 'і',
    'I', 'i',
    'Я', 'я',
    'Е', 'е',
    'Ё', 'ё',
    'Ю', 'ю',
};

utf8str translateCyrLat(utf8str str) {
    utf8str out{};
    for (int i = 0; i < str.size(); i++) {
        switch (static_cast<int>(str[i])) {
        case 'А':
            out.push_back('A');
            break;
        case 'а':
            out.push_back('a');
            break;
        case 'Б':
            out.push_back('B');
            break;
        case 'б':
            out.push_back('b');
            break;
        case 'В':
            out.push_back('V');
            break;
        case 'в':
            out.push_back('v');
            break;
        case 'Г':
            out.push_back('H');
            break;
        case 'г':
            out.push_back('h');
            break;
        case 'Ґ':
            out.push_back('G');
            break;
        case 'ґ':
            out.push_back('g');
            break;
        case 'Д':
            out.push_back('D');
            break;
        case 'д':
            out.push_back('d');
            break;
        case 'Е':
            if (i > 0 && (str[i - 1] == 'Л' || str[i - 1] == 'л'))
                out.push_back('E');
            else if (i > 0 && HAL_HUKI.contains(str[i - 1]))
                out.append("JE");
            else if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                out.append("Je");
            else
                out.append("IE");
            break;
        case 'е':
            if (i > 0 && (str[i - 1] == 'Л' || str[i - 1] == 'л'))
                out.push_back('e');
            else if (i > 0 && HAL_HUKI.contains(str[i - 1]))
                out.append("je");
            else if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                out.append("je");
            else
                out.append("ie");
            break;
        case 'Ё':
            if (i > 0 && (str[i - 1] == 'Л' || str[i - 1] == 'л'))
                out.push_back('O');
            else if (i > 0 && HAL_HUKI.contains(str[i - 1]))
                out.append("JO");
            else if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                out.append("Jo");
            else
                out.append("IO");
            break;
        case 'ё':
            if (i > 0 && (str[i - 1] == 'Л' || str[i - 1] == 'л'))
                out.push_back('o');
            else if (i > 0 && HAL_HUKI.contains(str[i - 1]))
                out.append("jo");
            else if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                out.append("jo");
            else
                out.append("io");
            break;
        case 'Ж':
            out.push_back('Ž');
            break;
        case 'ж':
            out.push_back('ž');
            break;
        case 'З':
            if (i < str.size() - 1 && (str[i + 1] == 'Ь' || str[i + 1] == 'ь'))
                out.push_back('Ź');
            else if (i < str.size() - 2 && !HAL_HUKI.contains(str[i + 1]) && !NIEPIER_HUKI.contains(str[i + 1]) && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('Ź');
            else if (i < str.size() - 3 && (str[i + 1] == 'Д' || str[i + 1] == 'д') && (str[i + 2] == 'З' || str[i + 2] == 'з') && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('Ź');
            else
                out.push_back('Z');
            break;
        case 'з':
            if (i < str.size() - 1 && (str[i + 1] == 'Ь' || str[i + 1] == 'ь'))
                out.push_back('ź');
            else if (i < str.size() - 2 && !HAL_HUKI.contains(str[i + 1]) && !NIEPIER_HUKI.contains(str[i + 1]) && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('ź');
            else if (i < str.size() - 3 && (str[i + 1] == 'Д' || str[i + 1] == 'д') && (str[i + 2] == 'З' || str[i + 2] == 'з') && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('ź');
            else
                out.push_back('z');
            break;
        case 'І':
            out.push_back('I');
            break;
        case 'і':
            out.push_back('i');
            break;
        case 'I':
            out.push_back('I');
            break;
        case 'i':
            out.push_back('i');
            break;
        case 'Й':
            out.push_back('J');
            break;
        case 'й':
            out.push_back('j');
            break;
        case 'К':
            out.push_back('K');
            break;
        case 'к':
            out.push_back('k');
            break;
        case 'Л':
            if (i < str.size() - 1 && MIAK_HUKI.contains(str[i + 1]))
                out.push_back('L');
            else
                out.push_back('Ł');
            break;
        case 'л':
            if (i < str.size() - 1 && MIAK_HUKI.contains(str[i + 1]))
                out.push_back('l');
            else
                out.push_back('ł');
            break;
        case 'М':
            out.push_back('M');
            break;
        case 'м':
            out.push_back('m');
            break;
        case 'Н':
            if (i < str.size() - 1 && (str[i + 1] == 'Ь' || str[i + 1] == 'ь'))
                out.push_back('Ń');
            else if (i < str.size() - 2 && !HAL_HUKI.contains(str[i + 1]) && !NIEPIER_HUKI.contains(str[i + 1]) && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('Ń');
            else if (i < str.size() - 3 && (str[i + 1] == 'Д' || str[i + 1] == 'д') && (str[i + 2] == 'З' || str[i + 2] == 'з') && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('Ń');
            else
                out.push_back('N');
            break;
        case 'н':
            if (i < str.size() - 1 && (str[i + 1] == 'Ь' || str[i + 1] == 'ь'))
                out.push_back('ń');
            else if (i < str.size() - 2 && !HAL_HUKI.contains(str[i + 1]) && !NIEPIER_HUKI.contains(str[i + 1]) && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('ń');
            else if (i < str.size() - 3 && (str[i + 1] == 'Д' || str[i + 1] == 'д') && (str[i + 2] == 'З' || str[i + 2] == 'з') && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('ń');
            else
                out.push_back('n');
            break;
        case 'О':
            out.push_back('O');
            break;
        case 'о':
            out.push_back('o');
            break;
        case 'П':
            out.push_back('P');
            break;
        case 'п':
            out.push_back('p');
            break;
        case 'Р':
            out.push_back('R');
            break;
        case 'р':
            out.push_back('r');
            break;
        case 'С':
            if (i < str.size() - 1 && (str[i + 1] == 'Ь' || str[i + 1] == 'ь'))
                out.push_back('Ś');
            else if (i < str.size() - 2 && !HAL_HUKI.contains(str[i + 1]) && !NIEPIER_HUKI.contains(str[i + 1]) && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('Ś');
            else if (i < str.size() - 3 && (str[i + 1] == 'Д' || str[i + 1] == 'д') && (str[i + 2] == 'З' || str[i + 2] == 'з') && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('Ś');
            else
                out.push_back('S');
            break;
        case 'с':
            if (i < str.size() - 1 && (str[i + 1] == 'Ь' || str[i + 1] == 'ь'))
                out.push_back('ś');
            else if (i < str.size() - 2 && !HAL_HUKI.contains(str[i + 1]) && !NIEPIER_HUKI.contains(str[i + 1]) && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('ś');
            else if (i < str.size() - 3 && (str[i + 1] == 'Д' || str[i + 1] == 'д') && (str[i + 2] == 'З' || str[i + 2] == 'з') && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('ś');
            else
                out.push_back('s');
            break;
        case 'Т':
            out.push_back('T');
            break;
        case 'т':
            out.push_back('t');
            break;
        case 'У':
            out.push_back('U');
            break;
        case 'у':
            out.push_back('u');
            break;
        case 'Ў':
            out.push_back('Ŭ');
            break;
        case 'ў':
            out.push_back('ŭ');
            break;
        case 'Ф':
            out.push_back('F');
            break;
        case 'ф':
            out.push_back('f');
            break;
        case 'Х':
            if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                out.append("Ch");
            else
                out.append("CH");
            break;
        case 'х':
            out.append("ch");
            break;
        case 'Ц':
            if (i < str.size() - 1 && (str[i + 1] == 'Ь' || str[i + 1] == 'ь'))
                out.push_back('Ć');
            else if (i < str.size() - 2 && !HAL_HUKI.contains(str[i + 1]) && !NIEPIER_HUKI.contains(str[i + 1]) && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('Ć');
            else if (i < str.size() - 3 && (str[i + 1] == 'Д' || str[i + 1] == 'д') && (str[i + 2] == 'З' || str[i + 2] == 'з') && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('Ć');
            else
                out.push_back('C');
            break;
        case 'ц':
            if (i < str.size() - 1 && (str[i + 1] == 'Ь' || str[i + 1] == 'ь'))
                out.push_back('ć');
            else if (i < str.size() - 2 && !HAL_HUKI.contains(str[i + 1]) && !NIEPIER_HUKI.contains(str[i + 1]) && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('ć');
            else if (i < str.size() - 3 && (str[i + 1] == 'Д' || str[i + 1] == 'д') && (str[i + 2] == 'З' || str[i + 2] == 'з') && MIAK_HUKI.contains(str[i + 2]))
                out.push_back('ć');
            else
                out.push_back('c');
            break;
        case 'Ч':
            out.push_back('Č');
            break;
        case 'ч':
            out.push_back('č');
            break;
        case 'Ш':
            out.push_back('Š');
            break;
        case 'ш':
            out.push_back('š');
            break;
        case 'Ы':
            out.push_back('Y');
            break;
        case 'ы':
            out.push_back('y');
            break;
        case 'Э':
            out.push_back('E');
            break;
        case 'э':
            out.push_back('e');
            break;
        case 'Ю':
            if (i > 0 && (str[i - 1] == 'Л' || str[i - 1] == 'л'))
                out.push_back('U');
            else if (i > 0 && HAL_HUKI.contains(str[i - 1]))
                out.append("JU");
            else if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                out.append("Ju");
            else
                out.append("IU");
            break;
        case 'ю':
            if (i > 0 && (str[i - 1] == 'Л' || str[i - 1] == 'л'))
                out.push_back('u');
            else if (i > 0 && HAL_HUKI.contains(str[i - 1]))
                out.append("ju");
            else if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                out.append("ju");
            else
                out.append("iu");
            break;
        case 'Я':
            if (i > 0 && (str[i - 1] == 'Л' || str[i - 1] == 'л'))
                out.push_back('A');
            else if (i > 0 && HAL_HUKI.contains(str[i - 1]))
                out.append("JA");
            else if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                out.append("Ja");
            else
                out.append("IA");
            break;
        case 'я':
            if (i > 0 && (str[i - 1] == 'Л' || str[i - 1] == 'л'))
                out.push_back('a');
            else if (i > 0 && HAL_HUKI.contains(str[i - 1]))
                out.append("ja");
            else if (i == 0 || (i > 0 && (std::iswspace(str[i - 1]) || std::iswpunct(str[i - 1]))))
                out.append("ja");
            else
                out.append("ia");
            break;
        case 'Ь': case 'ь': case '\'': case '’':
            break;
        default:
            out.push_back(str[i]);
        }
    }
    return out;
}