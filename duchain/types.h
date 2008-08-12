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

#ifndef JAVA_TYPES_H
#define JAVA_TYPES_H

#include <language/duchain/types/alltypes.h>

namespace java {

#if 0

class ParameterizedType : public ClassType
{
public:
  typedef KSharedPtr<ParameterizedType> Ptr;

  ParameterizedType(TypeModifiers modifiers = NoModifier);

  QList<AbstractType::Ptr> parameterTypes() const;
  void addParameterType(AbstractType::Ptr type);
  void clearParameterTypes();

  virtual uint hash() const;

  virtual QString toString() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;

  virtual void accept0 (KDevelop::TypeVisitor *v) const;

private:
  QList<AbstractType::Ptr> m_parameterTypes;
};

class WildcardType : public KDevelop::AbstractType, public JavaType
{
public:
  typedef KSharedPtr<WildcardType> Ptr;

  WildcardType();

  bool hasExtends() const;
  ClassType::Ptr extendsType() const;
  void setExtendsType(ClassType::Ptr extends);

  bool hasSuper() const;
  ClassType::Ptr superType() const;
  void setSuperType(ClassType::Ptr super);

  virtual QString toString() const;

  virtual uint hash() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;

  virtual void accept0 (KDevelop::TypeVisitor *v) const;

private:
  ClassType::Ptr m_extendsType, m_superType;
};
#endif

}

#endif // JAVA_TYPES_H

