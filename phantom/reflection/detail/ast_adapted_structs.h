

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::name,
    (phantom::reflection::cpp::ast::string_node, m_identifier)
    (boost::optional<phantom::vector<phantom::reflection::cpp::ast::template_element> >, m_template_signature)
    );
/*

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::qualified_name,
    (phantom::vector<phantom::reflection::cpp::ast::name>, m_names)
    );*/

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::cpp::ast::type,
    (boost::optional<phantom::reflection::cpp::ast::fundamental_node<char> >, m_const_modifier)
    (phantom::reflection::cpp::ast::qualified_name, m_qualified_name)
    (phantom::vector<phantom::reflection::cpp::ast::qualifier_or_extent>, m_type_extension)
    );

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::cpp::ast::element,
    (phantom::reflection::cpp::ast::type, m_type)
    (boost::optional<phantom::reflection::cpp::ast::function_prototype>, m_function_prototype)
);

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::cpp::ast::function_prototype,
    (phantom::reflection::cpp::ast::function_signature, m_signature)
    (boost::optional<phantom::reflection::cpp::ast::fundamental_node<char> >, m_const_modifier)
);

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::cast_expression,
    (phantom::reflection::cpp::ast::type, m_type)
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_casted_expression)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::pre_unary_expression ,
    (phantom::vector<phantom::reflection::cpp::ast::fundamental_node<size_t> >, m_ops)
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_expression)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::post_unary_expression ,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_expression)
    (phantom::vector<phantom::reflection::cpp::ast::fundamental_node<size_t> >, m_ops)
    );


BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::binary_op_right_expression,
    (phantom::reflection::cpp::ast::fundamental_node<size_t>, m_op)
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_right)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::binary_op_left_expression,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_left)
    (phantom::reflection::cpp::ast::fundamental_node<size_t>, m_op)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::binary_right_expression,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_left)
    (phantom::vector<phantom::reflection::cpp::ast::binary_op_right_expression>, m_op_rights)
    );
/*

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::binary_left_expression,
    (phantom::vector<phantom::reflection::cpp::ast::binary_op_left_expression>, m_op_lefts)
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_right)
    );*/

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::ternary_if_expression,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_condition)
    (phantom::vector<phantom::reflection::cpp::ast::ternary_if_expression_result>, m_results)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::ternary_if_expression_result,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_true)
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_false)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::call_expression,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::post_unary_expression>, m_left)
    (phantom::vector<phantom::reflection::cpp::ast::argument_list>, m_argument_lists)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::bracket_expression,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::call_expression>, m_left)
    (phantom::vector<phantom::reflection::cpp::ast::expression>, m_arguments)
    );

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::cpp::ast::block,
    (phantom::reflection::cpp::ast::statements, m_statements)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::extra_variable_declarator,
    (phantom::vector<phantom::reflection::cpp::ast::fundamental_node<char> >, m_type_qualifiers)
    (phantom::reflection::cpp::ast::variable_declarator, m_variable_declarator)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::array_initializer,
    (phantom::vector<phantom::reflection::cpp::ast::expression>, m_expressions)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::argument_list,
    (phantom::vector<phantom::reflection::cpp::ast::expression>, m_expressions)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast:: variable_declarator_end,
    (phantom::vector<phantom::reflection::cpp::ast::template_element>, m_extents)
    (boost::optional<phantom::reflection::cpp::ast::array_initializer_or_expression>, m_array_initializer_or_expression)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::variable_declarator,
    (phantom::reflection::cpp::ast::string_node, m_identifier)
    (phantom::reflection::cpp::ast::variable_declarator_end, m_end)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::variable_declaration,
    (boost::optional<phantom::reflection::cpp::ast::fundamental_node<bool> >, m_is_static)
    (phantom::reflection::cpp::ast::type, m_type)
    (phantom::reflection::cpp::ast::variable_declarator, m_declarator)
    (phantom::reflection::cpp::ast::extra_variable_declarators, m_extra_declarators)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::if_statement,
    (phantom::reflection::cpp::ast::variable_declaration_or_expression, m_condition)
(phantom::reflection::cpp::ast::statement, m_then)
(boost::optional<phantom::reflection::cpp::ast::statement>, m_else)
);


BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::goto_statement,
    (phantom::reflection::cpp::ast::string_node, m_label)
    );


BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::label_statement,
    (phantom::reflection::cpp::ast::string_node, m_label)
    );


BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::for_statement,
    (boost::optional<phantom::reflection::cpp::ast::variable_declaration_or_expression>, m_init)
    (boost::optional<phantom::reflection::cpp::ast::expression>, m_condition)
    (phantom::vector<phantom::reflection::cpp::ast::expression>, m_update)
    (boost::optional<phantom::reflection::cpp::ast::statement>, m_statement)
    );


BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::while_statement,
    (phantom::reflection::cpp::ast::variable_declaration_or_expression, m_condition)
    (boost::optional<phantom::reflection::cpp::ast::statement>, m_statement)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::do_while_statement,
    (boost::optional<phantom::reflection::cpp::ast::statement>, m_statement)
    (phantom::reflection::cpp::ast::expression, m_condition)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::switch_statement,
    (phantom::reflection::cpp::ast::variable_declaration_or_expression, m_test_value)
    (phantom::reflection::cpp::ast::statement_or_case_labels, m_statement_or_case_labels)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::return_statement,
    (boost::optional<phantom::reflection::cpp::ast::expression>, m_return_value)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::parameter,
    (phantom::reflection::cpp::ast::type, m_type)
    (boost::optional<phantom::reflection::cpp::ast::variable_declarator>, m_declarator)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::member_function_signature,
    (phantom::reflection::cpp::ast::parameters, m_parameters)
    (boost::optional<phantom::reflection::cpp::ast::fundamental_node<char> >, m_const)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::static_function_signature,
    (phantom::reflection::cpp::ast::parameters, m_parameters)
);


BOOST_FUSION_ADAPT_STRUCT(  phantom::reflection::cpp::ast::ambiguous_member_declaration_signature_and_block,
    (phantom::reflection::cpp::ast::member_function_signature, m_signature)
    (boost::optional<phantom::reflection::cpp::ast::block>, m_block)
);

BOOST_FUSION_ADAPT_STRUCT(  phantom::reflection::cpp::ast::ambiguous_member_declaration ,
    (phantom::reflection::cpp::ast::type, m_type )
    (phantom::reflection::cpp::ast::string_node, m_identifier )
    (boost::optional<phantom::reflection::cpp::ast::ambiguous_member_declaration_signature_and_block>, m_signature_and_block)
    );

BOOST_FUSION_ADAPT_STRUCT(  phantom::reflection::cpp::ast::static_ambiguous_member_declaration_signature_and_block,
    (phantom::reflection::cpp::ast::static_function_signature, m_signature)
    (boost::optional<phantom::reflection::cpp::ast::block>, m_block)
    );

BOOST_FUSION_ADAPT_STRUCT(  phantom::reflection::cpp::ast::static_ambiguous_member_declaration ,
    (phantom::reflection::cpp::ast::type, m_type )
    (phantom::reflection::cpp::ast::string_node, m_identifier )
    (boost::optional<phantom::reflection::cpp::ast::static_ambiguous_member_declaration_signature_and_block>, m_signature_and_block)
    );


BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::ambiguous_global_declaration_signature_and_block ,
    (phantom::reflection::cpp::ast::static_function_signature, m_signature)
    (boost::optional<phantom::reflection::cpp::ast::block>, m_block)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::ambiguous_global_declaration ,
    (boost::optional<phantom::reflection::cpp::ast::fundamental_node<bool> >, m_is_static)
    (phantom::reflection::cpp::ast::type, m_type )
    (phantom::reflection::cpp::ast::string_node, m_identifier )
    (boost::optional<phantom::reflection::cpp::ast::ambiguous_global_declaration_signature_and_block_or_declarator>, m_signature_and_block)
);

BOOST_FUSION_ADAPT_STRUCT(  phantom::reflection::cpp::ast::virtual_member_function_declaration ,
    (phantom::reflection::cpp::ast::type, m_return_type)
    (phantom::reflection::cpp::ast::string_node, m_identifier )
    (phantom::reflection::cpp::ast::member_function_signature, m_signature)
    (boost::optional<phantom::uint>, m_abstract)
    (boost::optional<phantom::reflection::cpp::ast::block>, m_block)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::class_inheritance,
    (phantom::reflection::cpp::ast::fundamental_node<unsigned long long>, m_access_specifier)
    (phantom::reflection::cpp::ast::qualified_name, m_qualified_name)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::class_scope, 
    (phantom::reflection::cpp::ast::class_inheritances, m_class_inheritances)
    (phantom::reflection::cpp::ast::class_member_declarations, m_class_member_declarations)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::namespace_declaration, 
    (phantom::reflection::cpp::ast::string_node, m_name)
    (phantom::reflection::cpp::ast::namespace_alias_or_scope, m_alias_or_scope)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::class_declaration, 
    (phantom::reflection::cpp::ast::fundamental_node<bool>, m_is_struct)
    (phantom::reflection::cpp::ast::named_or_unnamed_class_declaration, m_named_or_unnamed_class_declaration)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::class_variable_declarator, 
    (phantom::reflection::cpp::ast::variable_declarator, m_variable_declarator)
    (phantom::reflection::cpp::ast::extra_variable_declarators, m_extra_variable_declarators)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::case_label, 
    (boost::optional<phantom::reflection::cpp::ast::template_element>, m_value)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::named_class_declaration, 
    (phantom::reflection::cpp::ast::string_node, m_name)
    (boost::optional<phantom::reflection::cpp::ast::class_scope>, m_class_scope)
    (boost::optional<phantom::reflection::cpp::ast::class_variable_declarator>, m_variable_declarator)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::unnamed_class_declaration, 
    (phantom::reflection::cpp::ast::class_scope, m_class_scope)
    (phantom::reflection::cpp::ast::class_variable_declarator, m_variable_declarator)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::typedef_declaration, 
    (phantom::reflection::cpp::ast::type_or_class_declaration, m_type)
    (phantom::reflection::cpp::ast::string_node, m_name)
    );

namespace boost { namespace spirit { namespace traits
{
    template <typename Out, typename T>
    struct print_attribute_debug<Out, boost::recursive_wrapper<T> >
    {
        static void call(Out& out, boost::recursive_wrapper<T> const& val)
        {
            // do your output here; Out is a std::ostream
            print_attribute_debug<Out, T>::call(out, val.get());
        }
    };
    template <typename Out, typename T>
    struct print_attribute_debug<Out, phantom::vector<T> >
    {
        static void call(Out& out, phantom::vector<T> const& val)
        {
            // do your output here; Out is a std::ostream
            for(auto it = val.begin(); it != val.end(); ++it)
            {
                if(it != val.begin()) 
                    out << ' ';
                print_attribute_debug<Out, T>::call(out, *it);
            }
        }
    };
}}}