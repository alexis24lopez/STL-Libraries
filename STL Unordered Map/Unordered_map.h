/****************************************************************************************
* Alexis Lopez
* Unordered_map.h
* 03/07/18
* this class allows to store multiple values on the same index of a vector, and it has 
* a key that is used to find the specific value that the user want to use/ store. It 
* includes other functions that allows the user the interact with unordered maps.
****************************************************************************************/
#ifndef UNORDERED_H
#define UNORDERED_H

#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

template <class Key, class Value>
ostream & operator<<(ostream & out, const pair<Key, Value> & in)
{
    out << "(" << in.first << ":" << in.second << ")";
    return out;
}

template <typename Key>
class Hasher
{
public:
    unsigned operator()(const Key & k) const;
};

template <>
class Hasher<string>
{
public:
    unsigned operator()(const string & k) const
    {
        unsigned hashVal = 0;

        for (char ch: k)
            hashVal = 37 * hashVal + ch;

        return hashVal;
    }
};

template <>
class Hasher<unsigned>
{
public:
    unsigned operator()(const unsigned & k) const
    {
        return k%37;
    }
};

template <typename Key, typename Value, template <typename> class Hash> class Hash_iterator; 

template <typename Key, typename Value, template <typename> class Hash = Hasher>
class Unordered_map
{
private:
    unsigned num_buckets;
    vector< list< pair<Key, Value> > > bucket;
    Hash<Key> hashFunc;
    unsigned theSize;

    // set bucket index based on key, if key is found in bucket[index] return true and set i 
    bool find(const Key & key, unsigned & index, typename list< pair<Key, Value> >::iterator & i)
    {
        index = hashFunc(key)%num_buckets;

        for (i = bucket[index].begin(); i != bucket[index].end(); i++)
            if (i->first == key)
                break;

        if (i != bucket[index].end()) // found it
            return true;
        return false;
    }

public:
        
    typedef Hash_iterator<Key, Value, Hash> iterator;

    Unordered_map(unsigned count = 11): num_buckets(count), hashFunc(Hash<Key>()), theSize(0) 
    { 
        bucket = vector< list< pair<Key, Value> > >(num_buckets); 
    }

    ~Unordered_map() = default;

    Unordered_map(const Unordered_map & rhs): num_buckets{rhs.num_buckets}, 
        hashFunc{rhs.hashFunc}, theSize{0}
    {
        bucket = vector< list< pair<Key, Value> > >(num_buckets); 

        typename list< pair<Key, Value> >::const_iterator j;
        for (int i = 0; i < rhs.num_buckets; i++)
            for (j = rhs.bucket[i].begin(); j != rhs.bucket[i].end(); j++)
                insert(*j);
    }

    Unordered_map(Unordered_map && rhs): num_buckets{rhs.num_buckets}, 
        bucket{move(rhs.bucket)}, hashFunc{rhs.hashFunc}, theSize{rhs.theSize} { }

    Unordered_map & operator=(const Unordered_map & rhs)
    {
        Unordered_map<Key, Value, Hash> copy{rhs};
        swap(*this, copy);
        return *this;
    }

    Unordered_map & operator=(Unordered_map && rhs)
    {
        swap(num_buckets, rhs.num_buckets);
        swap(bucket, rhs.bucket);
        swap(hashFunc, rhs.hashFunc);
        swap(theSize, rhs.theSize);
        return *this;
    }

    unsigned bucket_count()
    {
        return num_buckets;
    }

    unsigned size()
    {
        return theSize;
    }

    unsigned bucket_size(unsigned n)
    {
        if (n >= num_buckets)
            return 0;

        return bucket[n].size();
    }

    // op[]: access a pair with "key", if it doesn't exist create an empty pair.
    Value & operator[](const Key & key)
    {
        unsigned index;
        typename list< pair<Key, Value> >::iterator i;

        if (find(key, index, i))
            return i->second;

        // not found, insert pair(key, default)
        bucket[index].push_front(pair<Key, Value>(key, Value()));
        theSize++;
        return bucket[index].front().second;
    }

    Value & operator[](Key && key)
    {
        unsigned index;
        typename list< pair<Key, Value> >::iterator i;

        if (find(key, index, i))
            return i->second;

        bucket[index].push_front(pair<Key, Value>(move(key), Value()));
        theSize++;
        return bucket[index].front().second;
    }

    void insert(const pair<Key, Value> & r)
    {
        unsigned index;
        typename list< pair<Key, Value> >::iterator i;

        if (find(r.first, index, i))
            *i = r;
        else { // not found, insert the new pair
            bucket[index].push_front(r);
            theSize++;
        }
    }

    void insert(pair<Key, Value> && r)
    {
        unsigned index;
        typename list< pair<Key, Value> >::iterator i;

        if (find(r.first, index, i))
            *i = move(r);
        else { 
            bucket[index].push_front(move(r));
            theSize++;
        }
    }

    // list all entries
    void print()
    {
        for (int i = 0; i < num_buckets; i++) {
            cout << "bucket[" << i << "] size=" << bucket_size(i) << " ";

            typename list< pair<Key, Value> >::iterator j;
            for (j = bucket[i].begin(); j != bucket[i].end(); j++)
                cout << *j << " ";
            cout << endl;
        }
    }

    iterator begin()
    {
        iterator iter(this);

        // find first non-empty bucket
        unsigned index = 0;
        while (index < num_buckets and bucket[index].size() == 0)
            ++index;
        if (index < num_buckets) {
            iter.bucket_index = index;
            iter.current = bucket[index].begin();
        } else {
            iter.bucket_index = num_buckets-1;
            iter.current = bucket[num_buckets-1].end();
        }

        return iter;
    }

    iterator end()
    {
	iterator iter(this);

	iter.current = bucket[num_buckets - 1].end();
	iter.bucket_index = num_buckets - 1;

        return iter;
    }

    iterator find(const Key & key)
    {
	iterator iter(this);

        unsigned index = 0;
	
	typename list< pair<Key, Value> >::iterator itr;

	if(find(key, index, itr))
        {
	    iter.current = itr;
	    iter.bucket_index = index;
	}
	else
	{
	    iter.current = bucket[num_buckets - 1].end();
	    iter.bucket_index = num_buckets - 1;
	}
	
	return iter;
    }

    void erase(const Key & key)
    {
	unsigned index = 0;

	typename list< pair<Key, Value> >::iterator itr;

	if(find(key, index, itr))
	{
	    bucket[index].erase(itr);
	    theSize--;
	}
	else
	    ;
    }
    
    void rehash(unsigned n)
    {
        if (n <= num_buckets)
            return;

        Unordered_map<Key, Value, Hash> copy(n);

        iterator current, i = begin();
        while (i != end()) {
            current = i++;
            copy.insert(*current);
        }

        *this = move(copy);
    }


friend class Hash_iterator<Key, Value, Hash>;

};


template <typename Key, typename Value, template <typename> class Hash>
class Hash_iterator
{
    Unordered_map<Key, Value, Hash> *theMap;
    typename list< pair<Key, Value> >::iterator current;
    unsigned bucket_index;

public:
    Hash_iterator(Unordered_map<Key, Value, Hash> * m = nullptr): theMap{m} { }

   ~Hash_iterator() = default;

    Hash_iterator(const Hash_iterator & iter): theMap{iter.theMap}, current{iter.current}, 
        bucket_index{iter.bucket_index} { }
    
    Hash_iterator(Hash_iterator && iter): theMap{iter.theMap}, current{move(iter.current)}, 
        bucket_index{iter.bucket_index} { iter.theMap = nullptr; }
    
    Hash_iterator & operator=(const Hash_iterator & iter)
    {
        theMap = iter.theMap;
        current = iter.current;
        bucket_index = iter.bucket_index;
        return *this; 
    }
    
    Hash_iterator & operator=(Hash_iterator && iter)
    {
        swap(theMap, iter.theMap);
        swap(current, iter.current);
        swap(bucket_index, iter.bucket_index);
        return *this;
    }
    
    Hash_iterator & operator++()
    {
        if (current == theMap->bucket[theMap->num_buckets-1].end())
            return *this;

        ++current;
        if (current == theMap->bucket[bucket_index].end()) {
            // at end of current bucket list, find next non-empty bucket
            ++bucket_index;
            while (bucket_index < theMap->num_buckets and theMap->bucket[bucket_index].size() == 0)
                ++bucket_index;
            if (bucket_index < theMap->num_buckets)
                current = theMap->bucket[bucket_index].begin();
            else
                current = theMap->bucket[theMap->num_buckets-1].end();
        }
        return *this;
    }

    Hash_iterator operator++(int)
    {
        Hash_iterator copy = *this;
        ++(*this);
        return copy;
    }

    pair<Key, Value> & operator*()
    {
	return *current;
    }

    typename list< pair<Key, Value> >::iterator operator->()
    {
	return current;
    }

    bool operator==(const Hash_iterator & val)
    {
	return current == val.current;
    }

    bool operator!=(const Hash_iterator & val)
    {
	return current != val.current;
    }

friend class Unordered_map<Key, Value, Hash>;
};

#endif
