#include "lexer.hpp"

void push_lexertl_rules(lexertl::rules &rules_) {
	for (macro_pair *ptr_ = g_macros_; ptr_->_name; ++ptr_) {
		rules_.insert_macro(ptr_->_name, ptr_->_regex);
	}
	for (rule_pair *ptr_ = g_regexes_; ptr_->_regex; ++ptr_) {
		rules_.push(ptr_->_regex, ptr_->_id);
	}
}
}