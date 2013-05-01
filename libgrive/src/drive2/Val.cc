/*
	grive: an GPL program to sync a local directory with Google Drive
	Copyright (C) 2013 Wan Wai Ho

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation version 2
	of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
	MA  02110-1301, USA.
*/

#include "Val.hh"

#include <iostream>

namespace gr {

Val::Val( ) :
	m_base( new Impl<void> )
{
}

Val::Val( const Val& v ) :
	m_base( v.m_base->Clone() )
{
}

Val::~Val()
{
}

Val::TypeEnum Val::Type() const
{
	return m_base->Type() ;
}

const Val& Val::operator[]( const std::string& key ) const
{
	const Object& obj = As<Object>() ;
	Object::const_iterator i = obj.find(key) ;
	if ( i != obj.end() )
		return i->second ;
	
	// shut off compiler warning
	BOOST_THROW_EXCEPTION(Error() << NoKey_(key)) ;
	throw ;
}

const Val& Val::operator[]( std::size_t index ) const
{
	const Array& ar = As<Array>() ;
	if ( index < ar.size() )
		return ar[index] ;
	
	// shut off compiler warning
	BOOST_THROW_EXCEPTION(Error() << OutOfRange_(index)) ;
	throw ;
}

void Val::Add( const std::string& key, const Val& value )
{
	As<Object>().insert( std::make_pair(key, value) ) ;
}

void Val::Swap( Val& val )
{
	std::swap( m_base, val.m_base ) ;
}

} // end of namespace

namespace std
{
	void swap( gr::Val& v1, gr::Val& v2 )
	{
		v1.Swap( v2 ) ;
	}
	
	ostream& operator<<( ostream& os, gr::Val::TypeEnum t )
	{
		return os << static_cast<int>(t) ;
	}
}
