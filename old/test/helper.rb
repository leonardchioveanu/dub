require 'rubygems'
require 'test/unit'
require 'shoulda'

$LOAD_PATH.unshift(File.join(File.dirname(__FILE__), '..', 'lib'))
$LOAD_PATH.unshift(File.dirname(__FILE__))
require 'dub'

class Test::Unit::TestCase

  def self.fixture(path)
    File.join(File.dirname(__FILE__), 'fixtures', path)
  end

  @@namespacecv_xml = nil

  Dub.logger.level = Logger::FATAL

  def fixture(path)
    self.class.fixture(path)
  end

  def namespacecv_xml
    @@namespacecv_xml ||= Dub.parse(fixture('namespacecv.xml'))
  end

  def namespacedub_xml
    @@namespacedub_xml ||= Dub.parse(fixture('app/xml/namespacedub.xml'))
  end

  def groupmagic_xml
    @@groupmagic_xml ||= Dub.parse(fixture('group___magic_type.xml'))
  end
end