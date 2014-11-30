#ifndef reflection_detail_element_finder_h__
#define reflection_detail_element_finder_h__

namespace phantom { class element_scanner; class element_parser; }

o_namespace_begin(phantom, reflection, detail)

class element_finder_spirit;

#include "phantom/def_export.h"

class o_export element_finder_spirit
{
  friend class phantom::element_scanner;
  friend class phantom::element_parser;
  friend class phantom::Phantom;
  friend o_export phantom::reflection::LanguageElement*    phantom::elementByName(const string&, phantom::reflection::LanguageElement*);

protected:
  element_finder_spirit();
  ~element_finder_spirit()
  {
  }

  /*reflection::LanguageElement*  solve(element_info* info);
  reflection::LanguageElement*  solve(element_info* info, reflection::LanguageElement* a_pElement);
*/
public:
  static LanguageElement*  eval(const string& a_strQualifiedName, LanguageElement* a_pRootElement = phantom::rootNamespace());

protected:
  void setFound(LanguageElement* a_pElement) { m_pElement = a_pElement; }

  LanguageElement*    rootElement() const { return m_pRootElement; }


protected:
  LanguageElement*          m_pElement;
  LanguageElement*          m_pRootElement;

};

o_namespace_end(phantom, reflection, detail)

#endif // reflection_detail_element_finder_h__