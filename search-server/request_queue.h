#pragma once

#include <deque>
#include "search_server.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);
    
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        std::vector<Document> result = search_server_.FindTopDocuments(raw_query, document_predicate);
        ++number_query_result;
        if (number_query_result > min_in_day_) {
            number_query_result = 1;
        }
        if (requests_.size() >= min_in_day_) {
            requests_.pop_front(); 
        }
       requests_.push_back({ static_cast<int>(result.size()), number_query_result });
       return search_server_.FindTopDocuments(raw_query, document_predicate);
    }
    
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string& raw_query);
    
    int GetNoResultRequests() const;
    
private:
    struct QueryResult {
        int count_results;
        int request_number;
    };
    
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    const SearchServer& search_server_;
    int  number_query_result = 0;
};