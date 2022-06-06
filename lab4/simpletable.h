#ifndef TEMPLATECLASS_TABLE_H
#define TEMPLATECLASS_TABLE_H
#include <iostream>

template <typename Key, typename T>
class ConstsimpletableIt{
private:
    const std::pair<Key, T>* cur;
public:
    ConstsimpletableIt(): cur(nullptr){};
    explicit ConstsimpletableIt(const std::pair<Key, T>* it):cur(it){};
    int operator != (const ConstsimpletableIt<Key, T>&);
    int operator == (const ConstsimpletableIt<Key, T>&);
    [[nodiscard]] const std::pair<Key, T>* getCur() const{return cur;};
    const std::pair<Key, T>& operator*();
    ConstsimpletableIt& operator ++ ();
    ConstsimpletableIt operator ++(int);
};
template<typename Key, typename T>
class simpletable{
private:
    static const int Quota = 10;
    int csize;
    int msize;
    std::pair<Key, T>* array;
public:
    simpletable():csize(0), msize(0),array(nullptr){};
    simpletable(const simpletable<Key, T>&);
    simpletable(simpletable<Key,T>&&) noexcept ;
    simpletable<Key, T>& operator=(const simpletable<Key, T>&);
    simpletable<Key, T>& operator=(simpletable<Key, T>&&) noexcept ;
    [[nodiscard]] int getcsize() const {return csize;};
    [[nodiscard]] int getmsize() const {return msize;};
    [[nodiscard]] std::pair<Key, T>* getarray() const {return array;};
    ~simpletable(){delete[]array;};
    T* find(const Key&) const;
    int findbIndex(const Key& key) const;
    simpletable<Key, T>& add(Key, T);
    simpletable<Key, T>* delItem(Key);
    std::pair<Key, T>& operator[](int i);
    std::pair<Key, T> operator[](int i) const;
    friend class ConstsimpletableIt<Key, T>;
    typedef ConstsimpletableIt<Key, T> ConstIterator;
    ConstIterator begin();
    ConstIterator end();
};
template<typename Key, typename T>
simpletable<Key, T>::simpletable(const simpletable<Key, T>& old): csize(old.csize), msize(old.msize){
    if(csize == 0) array = nullptr;
    else{
        array = new std::pair<Key, T>[old.csize];
        for(int i = 0; i < old.csize; i++){
            array[i] = old.array[i];
        }
    }
}
template <typename Key, typename T>
simpletable<Key, T>::simpletable(simpletable<Key, T> &&old) noexcept{
    csize = old.csize;
    msize = old.msize;
    array = old.array;
    old.array = nullptr;
}
template<typename Key, typename T>
simpletable<Key, T>& simpletable<Key, T>::operator=(const simpletable<Key, T> &old){
    if(this == &old) return *this;
    csize = old.csize;
    msize = old.msize;
    if(csize == 0) array = nullptr;
    else{
        array = new std::pair<Key, T>[old.csize];
        for(int i = 0; i < old.csize; i++){
            array[i] = old.array[i];
        }
    }
    return *this;
}
template<typename Key, typename T>
simpletable<Key, T>& simpletable<Key, T>::operator=(simpletable<Key, T> &&old) noexcept{
    if(this == &old) return *this;
    csize = old.csize;
    msize = old.msize;
    if(csize == 0) array = nullptr;
    auto tmp = array;
    array = old.array;
    old.array = tmp;
    return *this;
}
template<typename Key, typename T>
typename simpletable<Key,T>::ConstIterator simpletable<Key, T>::begin(){
    return simpletable::ConstIterator(array);
}
template<typename Key, typename T>
typename simpletable<Key,T>::ConstIterator simpletable<Key, T>::end(){
    return simpletable::ConstIterator(array + csize);
}
template<typename Key, typename T>
T* simpletable<Key, T>::find(const Key& key) const{
    for(int i = 0; i < csize; i++){
        if(array[i].first == key) return &array[i].second;
    }
    return nullptr;
}
template<typename Key, typename T>
int simpletable<Key, T>::findbIndex(const Key& key) const{
    for(int i = 0; i < csize; i++){
        if(array[i].first == key) return i;
    }
    return -1;
}

template<typename Key, typename T>
simpletable<Key, T>& simpletable<Key,T>::add(Key key, T t){
    if(!find(key)){
        auto pair = new std::pair<Key, T>(key, t);
        if(csize == msize){
            msize += Quota;
            std::pair<Key, T>* old = array;
            array = new std::pair<Key, T>[msize];
            for(int i = 0; i < csize; i++){
                array[i] = old[i];
            }
            delete[] old;
        }
        array[csize] = *pair;
        csize++;
    }
    return *this;
}

template<typename Key, typename T>
simpletable<Key, T>* simpletable<Key, T>::delItem(Key key){
    int i;
    if((i = findbIndex(key)) != -1){
        array[i] = array[csize - 1];
        csize--;
    }
    return nullptr;
}
template<typename Key, typename T>
std::pair<Key, T>& simpletable<Key, T>::operator[](const int i) {
    return array[i];
}
template<typename Key, typename T>
std::pair<Key, T> simpletable<Key, T>::operator[](const int i) const{
    return array[i];
}


//T& simpletable<Key, T>::find(const Key&) const{}
template<typename Key, typename T>
int ConstsimpletableIt<Key, T>::operator==(const ConstsimpletableIt<Key, T> &it){
    return cur == it.cur;
}
template<typename Key, typename T>
int ConstsimpletableIt<Key, T>::operator!=(const ConstsimpletableIt<Key, T> &it){
    return cur != it.cur;
}
template<typename Key, typename T>
const std::pair<Key, T>& ConstsimpletableIt<Key, T>::operator*(){
    if(cur){
        return *cur;
    }
    throw std::invalid_argument("illigal value for iterator");
}
template<typename Key, typename T>
ConstsimpletableIt<Key, T>& ConstsimpletableIt<Key, T>::operator++(){
    ++cur;
    return *this;
}
template<typename Key, typename T>
ConstsimpletableIt<Key, T> ConstsimpletableIt<Key, T>::operator++(int){
    ConstsimpletableIt res;
    res.cur = cur;
    ++cur;
    return res;
}



#endif //TEMPLATECLASS_TABLE_H
