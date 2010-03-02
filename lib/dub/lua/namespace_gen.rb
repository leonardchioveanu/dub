require 'dub/generator'
require 'erb'

module Dub
  module Lua
    class NamespaceGen < Dub::Generator
      def initialize
        @namespace_template = ::ERB.new(File.read(File.join(File.dirname(__FILE__), 'namespace.cpp.erb')))
      end

      def namespace(namespace)
        @namespace = namespace
        @namespace_template.result(binding)
      end

      def class_generator
        Lua.class_generator
      end

      def constants_registration(namespace = @namespace)
        res = []
        if namespace.has_enums?
          res << namespace.enums.map do |name|
            "{%-32s, #{namespace.full_type}::#{name}}" % name.inspect
          end.join(",\n")
        end

        if namespace.has_defines?
          res << namespace.defines.map do |name|
            "{%-32s, #{name}}" % name.inspect
          end.join(",\n")
        end

        same = namespace.enums & namespace.defines
        unless same.empty?
          # Should never happen (not sure if it would compile ok in the first place)
          puts "Warning: the following are present both as enum and define: #{same.inspect}"
        end
        res.join("\n\n")
      end
    end
  end
end