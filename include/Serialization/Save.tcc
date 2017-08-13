/*template<typename T>
void save(Archive<true>& a, T & t) {
    t.serialize(a);
}

template<>
inline void save<int> (Archive<true>& a, int & t) {
    a & t;
}

template<>
inline void save<long> (Archive<true>& a, long & t) {
    a & i;
}

template<>
inline void save<std::string> (Archive<true>& a, std::string & t) {
    a & i;
}
*/