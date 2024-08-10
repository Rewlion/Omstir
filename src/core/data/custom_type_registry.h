#pragma once

#include "concept.h"
#include "types.h"

#include <core/utils/hash.h>
#include <core/types.h>

#include <vector>
#include <unordered_map>

namespace ed
{
  class Scope;
}

namespace std {
  template <> struct hash<engine_data_type_id_t>
  {
    size_t operator()(const engine_data_type_id_t & x) const
    {
      return (size_t)x;
    }
  };
}


namespace ed
{
  class RegisteredCompileTypeId
  {
    public:
      template<class T>
      static
      auto from() -> engine_data_type_id_t
      {
        return fromInternal<typename std::remove_cvref<T>::type>();
      }

    private:
      template<class T>
      static
      auto fromInternal() -> engine_data_type_id_t
      {
        static engine_data_type_id_t id = engine_data_type_id_t{m_LastId++};
        return id;
      }

    private:
      static engine_data_type_id_t m_LastId;
  };

  class CustomTypeRegistry
  {
  public:
    struct Entry
    {
      engine_data_type_id_t compileTypeId;
      string name;
      string_hash nameHash;
    };
  
    template<class T>
    requires HasCtorForEngineData<T>
    void add(const char* type_name);
  
    auto get(string_view type_name) -> const Entry*;
    auto get(const engine_data_type_id_t& type_id) -> const Entry*;
  
    template<class T>
    auto get() -> const Entry*
    {
      return get(getTypeId<T>());
    }
  
    template<class T>
    auto getTypeId() -> engine_data_type_id_t
    {
      return RegisteredCompileTypeId::template from<T>();
    }
  
  private:
    std::vector<Entry> m_Entries;
    std::unordered_map<string_hash, size_t> m_NameHashToEntryId;
    std::unordered_map<engine_data_type_id_t, size_t> m_CompileTimeIdToEntryId;
  };

  template<class T>
  requires HasCtorForEngineData<T>
  void CustomTypeRegistry::add(const char* type_name)
  {
    const engine_data_type_id_t tId = RegisteredCompileTypeId::template from<T>();
    const string_hash nameHash = str_hash(type_name);
    
    const size_t entryId = m_Entries.size();

    m_Entries.push_back(Entry{
      .compileTypeId = tId,
      .name = string{type_name},
      .nameHash = nameHash
    });

    m_NameHashToEntryId.insert({nameHash, entryId});
    m_CompileTimeIdToEntryId.insert({tId, entryId});
  }
}
