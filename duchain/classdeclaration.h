/* This file is part of KDevelop
    Copyright 2008 David Nolden <david.nolden@kdevelop.org>
    Copyright 2008 Hamish Rodda <rodda@kde.org>

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

#ifndef CLASSDECLARATION_H
#define CLASSDECLARATION_H

#include <language/duchain/declaration.h>
#include <language/duchain/types/alltypes.h>

namespace KDevelop {
  class QualifiedIdentifier;
  class DUContext;
  class TopDUContext;
  class HashedString;
  class SimpleRange;
}

namespace java {

struct BaseClassInstance
{
  KDevelop::IndexedType baseClass; //May either be JavaClassType, or JavaDelayedType
  KDevelop::Declaration::AccessPolicy access;
  bool virtualInheritance;
};

class ClassDeclarationPrivate;

class ClassDeclaration : public KDevelop::Declaration
{
public:
  ClassDeclaration(const ClassDeclaration& rhs);
  ClassDeclaration(const KDevelop::SimpleRange& range, KDevelop::DUContext* context);
  ~ClassDeclaration();

  void clearBaseClasses();
  ///Count of base-classes
  uint baseClassesSize() const;
  ///The types this class is based on
  const BaseClassInstance* baseClasses() const;
  void addBaseClass(BaseClassInstance klass);
  //Replaces the n'th base-class with the given one. The replaced base-class must have existed.
  void replaceBaseClass(uint n, BaseClassInstance klass);

  virtual KDevelop::Declaration* clone() const;

private:
  ClassDeclarationPrivate* const d_ptr;
  Q_DECLARE_PRIVATE(ClassDeclaration)
};

}

#endif // FUNCTIONDECLARATION_H

