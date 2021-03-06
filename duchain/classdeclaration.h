/* This file is part of KDevelop
    Copyright 2008 David Nolden <david.nolden@kdevelop.org>
    Copyright 2008-2009 Hamish Rodda <rodda@kde.org>

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
#include <language/duchain/declarationdata.h>
#include <language/duchain/classmemberdeclarationdata.h>
#include <language/duchain/classmemberdeclaration.h>
#include <language/duchain/types/alltypes.h>

#include "javaduchain_export.h"

namespace KDevelop {
  class QualifiedIdentifier;
  class DUContext;
  class TopDUContext;
  class HashedString;
  class RangeInRevision;
}

namespace java {

struct BaseClassInstance
{
  KDevelop::IndexedType baseClass;
};

DECLARE_LIST_MEMBER_HASH(ClassDeclarationData, baseClasses, BaseClassInstance)

class ClassDeclarationData : public KDevelop::ClassMemberDeclarationData
{
public:
  enum ClassType {
    Class,
    Interface,
    Enum
  };

  ClassDeclarationData() : m_classType(Class) {
    initializeAppendedLists();
  }

  ~ClassDeclarationData() {
    freeAppendedLists();
  }

  ClassDeclarationData(const ClassDeclarationData& rhs) : KDevelop::ClassMemberDeclarationData(rhs) {
    initializeAppendedLists();
    copyListsFrom(rhs);
    m_classType = rhs.m_classType;
  }

  /// Type of the class (class or interface)
  ClassType m_classType;

  START_APPENDED_LISTS_BASE(ClassDeclarationData, KDevelop::ClassMemberDeclarationData);
  APPENDED_LIST_FIRST(ClassDeclarationData, BaseClassInstance, baseClasses);
  END_APPENDED_LISTS(ClassDeclarationData, baseClasses);
};


class KDEVJAVADUCHAIN_EXPORT ClassDeclaration : public KDevelop::ClassMemberDeclaration
{
public:

  ClassDeclaration(const ClassDeclaration& rhs);
  ClassDeclaration(ClassDeclarationData& data);
  ClassDeclaration(const KDevelop::RangeInRevision& range, KDevelop::DUContext* context);
  ~ClassDeclaration();

  enum StorageSpecifier {
      StaticSpecifier   = 0x1  /**< indicates static member */,
      AutoSpecifier     = 0x2  /**< indicates automatic determination of member access */,
      FriendSpecifier   = 0x4  /**< indicates friend member */,
      ExternSpecifier   = 0x8  /**< indicates external declaration */,
      RegisterSpecifier = 0x10 /**< indicates register */,
      MutableSpecifier  = 0x20 /**< indicates a mutable member */,
      FinalSpecifier    = 0x40 /**< indicates a final declaration */,
      NativeSpecifier   = 0x80,
      SynchronizedSpecifier = 0x100,
      StrictFPSpecifier = 0x200,
      AbstractSpecifier = 0x400
  };
  Q_DECLARE_FLAGS(StorageSpecifiers, StorageSpecifier)

  void setStorageSpecifiers(StorageSpecifiers specifiers);

  void clearBaseClasses();
  ///Count of base-classes
  uint baseClassesSize() const;
  ///The types this class is based on
  const BaseClassInstance* baseClasses() const;
  void addBaseClass(BaseClassInstance klass);
  //Replaces the n'th base-class with the given one. The replaced base-class must have existed.
  void replaceBaseClass(uint n, BaseClassInstance klass);

  /**Returns whether base is a public base-class of this class
   * @param baseConversionLevels If nonzero, this will count the distance of the classes.
   * */
  //bool isPublicBaseClass( ClassDeclaration* base, const KDevelop::TopDUContext* topContext, int* baseConversionLevels  = 0 ) const;

  virtual QString toString() const;

  void setClassType(ClassDeclarationData::ClassType type);

  ClassDeclarationData::ClassType classType() const;

  enum {
    Identity = 30
  };

private:
  virtual KDevelop::Declaration* clonePrivate() const;
  DUCHAIN_DECLARE_DATA(ClassDeclaration)

  bool m_isFinal        = false;
  bool m_isNative       = false;
  bool m_isSynchronized = false;
  bool m_isStrictFP     = false;
  bool m_isAbstract     = false;

};

}

#endif // FUNCTIONDECLARATION_H

