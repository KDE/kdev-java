/* This file is part of KDevelop
    Copyright 2002-2005 Roberto Raggi <roberto@kdevelop.org>
    Copyright 2006 Adam Treat <treat@kde.org>
    Copyright 2006-2008 Hamish Rodda <rodda@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "types.h"

using namespace KDevelop;
namespace java {

#if 0
ParameterizedType::ParameterizedType(TypeModifiers modifiers)
  : StructureType(modifiers)
{
}

QList< AbstractType::Ptr > ParameterizedType::parameterTypes() const
{
  return m_parameterTypes;
}

void ParameterizedType::addParameterType(AbstractType::Ptr type)
{
  m_parameterTypes.append(type);
}

void ParameterizedType::clearParameterTypes()
{
  m_parameterTypes.clear();
}

uint ParameterizedType::hash() const
{
  uint parameterHashes = 0;
  foreach (const AbstractType::Ptr& type, m_parameterTypes)
    parameterHashes += type->hash();

  return ClassType::hash() + 31 * parameterHashes;
}

QString ParameterizedType::toString() const
{
  QString ret = ClassType::toString() + "<";

  bool first = true;
  foreach (const AbstractType::Ptr& type, m_parameterTypes) {
    if (!first) ret += ", ";
    ret += type->toString();
  }

  return ret;
}

AbstractType * ParameterizedType::clone() const
{
  ParameterizedType* ret = static_cast<ParameterizedType*>(ClassType::clone());

  ret->m_parameterTypes = m_parameterTypes;

  return ret;
}

bool ParameterizedType::equals(const AbstractType * rhs) const
{
  if (const ParameterizedType* type = dynamic_cast<const ParameterizedType*>(rhs))
    if (type->ClassType::equals(rhs) && m_parameterTypes == type->m_parameterTypes)
      return true;

  return false;
}

void ParameterizedType::accept0(KDevelop::TypeVisitor * v) const
{
  v->visit(this);
}

WildcardType::WildcardType()
{
}

bool WildcardType::hasExtends() const
{
  return m_extendsType;
}

ClassType::Ptr WildcardType::extendsType() const
{
  return m_extendsType;
}

void WildcardType::setExtendsType(ClassType::Ptr extends)
{
  Q_ASSERT(!m_superType);
  m_extendsType = extends;
}

bool WildcardType::hasSuper() const
{
  return m_superType;
}

ClassType::Ptr WildcardType::superType() const
{
  return m_superType;
}

void WildcardType::setSuperType(ClassType::Ptr super)
{
  m_superType = super;
}

QString WildcardType::toString() const
{
  QString ret = "*";

  if (m_extendsType)
    ret += " extends " + m_extendsType->toString();

  if (m_superType)
    ret += " super " + m_superType->toString();

  return ret;
}

uint WildcardType::hash() const
{
  uint ret = 1;
  if (m_extendsType)
    ret += m_extendsType->hash() * 3;

  if (m_superType)
    ret += m_superType->hash() * 3;

  return ret;
}

bool WildcardType::equals(const AbstractType * rhs) const
{
  if (const WildcardType* wild = dynamic_cast<const WildcardType*>(rhs))
    if (wild->extendsType() == m_extendsType && wild->superType() == m_superType)
      return true;

  return false;
}

AbstractType * WildcardType::clone() const
{
  return new WildcardType(*this);
}

void WildcardType::accept0(TypeVisitor * v) const
{
  v->visit(this);
}

#endif

}
