/* This  is part of KDevelop
    Copyright 2007 David Nolden <david.nolden@kdevelop.org>
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

#include "classdeclaration.h"

#include <language/duchain/identifier.h>
#include <language/duchain/declaration.h>
#include <language/duchain/appendedlist.h>
#include <language/duchain/duchainregister.h>

using namespace KDevelop;

namespace java {

DEFINE_LIST_MEMBER_HASH(ClassDeclarationData, baseClasses, BaseClassInstance)

ClassDeclaration::ClassDeclaration(const KDevelop::RangeInRevision& range, DUContext* context)
  : ClassMemberDeclaration(*new ClassDeclarationData, range)
{
  d_func_dynamic()->setClassId(this);
  setContext(context);
}

ClassDeclaration::ClassDeclaration(ClassDeclarationData& data)
  : ClassMemberDeclaration(data)
{
}


REGISTER_DUCHAIN_ITEM(ClassDeclaration);


void ClassDeclaration::setStorageSpecifiers(StorageSpecifiers specifiers)
{
  ClassMemberDeclaration::setStorageSpecifiers(ClassMemberDeclaration::StorageSpecifiers(static_cast<ClassDeclaration::StorageSpecifiers::Int>(specifiers)));
  this->m_isFinal = specifiers & FinalSpecifier;
  this->m_isSynchronized = specifiers & SynchronizedSpecifier;
  this->m_isNative = specifiers & NativeSpecifier;
  this->m_isStrictFP = specifiers & StrictFPSpecifier;
  this->m_isAbstract = specifiers & AbstractSpecifier;
}

void ClassDeclaration::clearBaseClasses() {
  d_func_dynamic()->baseClassesList().clear();
}

uint ClassDeclaration::baseClassesSize() const {
  return d_func()->baseClassesSize();
}

const BaseClassInstance* ClassDeclaration::baseClasses() const {
  return d_func()->baseClasses();
}

void ClassDeclaration::addBaseClass(BaseClassInstance klass) {
  d_func_dynamic()->baseClassesList().append(klass);
}

void ClassDeclaration::replaceBaseClass(uint n, BaseClassInstance klass) {
  Q_ASSERT(n <= d_func_dynamic()->baseClassesSize());
  d_func_dynamic()->baseClassesList()[n] = klass;
}

ClassDeclaration::~ClassDeclaration()
{
}

ClassDeclaration::ClassDeclaration(const ClassDeclaration& rhs) : ClassMemberDeclaration(*new ClassDeclarationData(*rhs.d_func()))
{
  d_func_dynamic()->setClassId(this);
}

Declaration* ClassDeclaration::clonePrivate() const {
  return new ClassDeclaration(*this);
}

QString ClassDeclaration::toString() const {
  return (classType() == ClassDeclarationData::Class ? "class " : "interface ") + identifier().toString();
}

ClassDeclarationData::ClassType ClassDeclaration::classType() const {
  return d_func()->m_classType;
}

void ClassDeclaration::setClassType(java::ClassDeclarationData::ClassType type) {
  d_func_dynamic()->m_classType = type;
}

}
