#include <boost/property_tree_custom/ptree.hpp>
#include <boost/pool/pool.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/property_tree_custom/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <set>

struct malloc_free_allocator_for_boost
{
	typedef std::size_t		size_type;
	typedef std::ptrdiff_t	difference_type;

	static char * malloc BOOST_PREVENT_MACRO_SUBSTITUTION(const size_type bytes)
	{ return static_cast<char *>( ::malloc(bytes)); }
	static void free BOOST_PREVENT_MACRO_SUBSTITUTION(char * const block)
	{ ::free(block); }
};

typedef std::basic_string<char, std::char_traits<char>, ::boost::pool_allocator<char> > string;

struct debug_settings
{
	string m_file;          // log filename
	int m_level;                 // debug level
	std::set<string> m_modules;  // modules where logging is enabled
	void load(const string &filename);
	void save(const string &filename);

	bool operator==(const debug_settings& other) const
	{
		return m_file == other.m_file && m_level == other.m_level && m_modules == other.m_modules;
	}
};

// Loads debug_settings structure from the specified XML file
void debug_settings::load(const string &filename)
{
	// Create an empty property tree object
	using boost::property_tree_custom::ptree;
	ptree pt;

	// Load the XML file into the property tree. If reading fails
	// (cannot open file, parse error), an exception is thrown.
	read_xml(filename, pt);

	// Get the filename and store it in the m_file variable.
	// Note that we construct the path to the value by separating
	// the individual keys with dots. If dots appear in the keys,
	// a path type with a different separator can be used.
	// If the debug.filename key is not found, an exception is thrown.
	m_file = pt.get<string>("debug.filename");

	// Get the debug level and store it in the m_level variable.
	// This is another version of the get method: if the value is
	// not found, the default value (specified by the second
	// parameter) is returned instead. The type of the value
	// extracted is determined by the type of the second parameter,
	// so we can simply write get(...) instead of get<int>(...).
	m_level = pt.get("debug.level", 0);

	// Iterate over the debug.modules section and store all found
	// modules in the m_modules set. The get_child() function
	// returns a reference to the child at the specified path; if
	// there is no such child, it throws. Property tree iterators
	// are models of BidirectionalIterator.
	BOOST_FOREACH(ptree::value_type &v,
		pt.get_child("debug.modules"))
		m_modules.insert(v.second.data());
}

void debug_settings::save(const string &filename)
{
	// Create an empty property tree object
	using boost::property_tree_custom::ptree;
	ptree pt;

	// Put log filename in property tree
	pt.put("debug.filename", m_file);

	// Put debug level in property tree
	pt.put("debug.level", m_level);

	// Iterate over the modules in the set and put them in the
	// property tree. Note that the put function places the new
	// key at the end of the list of keys. This is fine most of
	// the time. If you want to place an item at some other place
	// (i.e. at the front or somewhere in the middle), this can
	// be achieved using a combination of the insert and put_own
	// functions.
	BOOST_FOREACH(const string &name, m_modules)
		pt.add("debug.modules.module", name);

	// Write the property tree to the XML file.
	write_xml(filename, pt);
}

int main()
{
	
	debug_settings test_sample;
	test_sample.load("resources/test_sample.xml");
	debug_settings ds = test_sample;
	ds.save("../resources/ds.xml");
	ds.load("../resources/ds.xml");

	assert(ds == test_sample);

	int i = 0;

	system("pause");
	return 0;
}