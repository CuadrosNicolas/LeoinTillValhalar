//fonction template pour convertir un chiffre en chaine de caract�re
template <typename T>
std::string fonction::convertToString(T a)
{
        std::ostringstream ss;
    ss << a;
    std::string s(ss.str());
    return s;
}
