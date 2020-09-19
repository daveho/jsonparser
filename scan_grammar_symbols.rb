#! /usr/bin/env ruby

# Generate grammar_symbols.h and grammar_symbols.c from grammar productions
# in parse.y

print "Generating grammar_symbols.h/grammar_symbols.c..."

START = 1000
first = true
grammar_symbol_names = []
num_productions = 0
TOKEN_START = 258   # bison token types start at 258
first_token = true
num_tokens = 0

header_fh = File.open('grammar_symbols.h', 'w')
source_fh = File.open('grammar_symbols.c', 'w')

header_fh.print <<"EOF1"
#ifndef GRAMMAR_SYMBOLS_H
#define GRAMMAR_SYMBOLS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

enum GrammarSymbol {
EOF1

STDIN.each_line do |line|
  if m = line.match(/^([a-z_]+)(\s*\/\*.*)?$/)
    grammar_symbol_names.push(m[1])
    header_fh.print "  NODE_#{m[1]}"
    header_fh.print " = #{START}" if first
    header_fh.puts ","
    first = false
    num_productions += 1
  elsif m = line.start_with?('%token<node> ')
    line = line['%token<node> '.length..line.length-1]
    #puts "Tokens!: #{line}"
    line.split(/\s+/).each do |token|
      grammar_symbol_names.push(token)
      header_fh.print "  NODE_#{token}"
      header_fh.print " = #{TOKEN_START}" if first_token
      header_fh.puts ","
      first_token = false
      num_tokens += 1
    end
  end
end

header_fh.print <<"EOF2"
};

// Get grammar symbol name corresponding to tag (enumeration value).
// Useful for making sense of a parse tree based on the tag values
// of the nodes.
const char *get_grammar_symbol_name(int tag);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // GRAMMAR_SYMBOLS_H
EOF2

source_fh.print <<"EOF3"
#include <stddef.h>

static const char *s_grammar_symbol_names[] = {
EOF3
grammar_symbol_names.each do |name|
  source_fh.puts "  \"#{name}\","
end

source_fh.print <<"EOF4"
};

const char *get_grammar_symbol_name(int tag) {
  if (tag < #{TOKEN_START}) {
    return NULL;
  }

  if (tag < #{START}) {
    // must be a token
    int which_token = tag - #{TOKEN_START};
    if (which_token >= #{num_tokens}) {
      return NULL;
    } else {
      return s_grammar_symbol_names[which_token];
    }
  }

  int which_production = tag - #{START};
  if (which_production >= #{num_productions}) {
    return NULL;
  }
  return s_grammar_symbol_names[#{num_tokens} + which_production];
}
EOF4

header_fh.close
source_fh.close

puts "Done!"
