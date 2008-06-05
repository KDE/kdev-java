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

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QPair>

#include <duchain/identifier.h>
#include <typesystem.h>
#include <declaration.h>
#include <identifiedtype.h>

namespace KDevelop
{
class DUContext;
class Declaration;
}

namespace java {

enum TypeModifiers {
  NoModifier           = 0,
  PrivateModifier      = 1,
  PublicModifier       = 1 << 1,
  ProtectedModifier    = 1 << 2,
  StaticModifier       = 1 << 3,
  TransientModifier    = 1 << 4,
  FinalModifier        = 1 << 5,
  AbstractModifier     = 1 << 6,
  NativeModifier       = 1 << 7,
  SynchronizedModifier = 1 << 8,
  VolatileModifier     = 1 << 9,
  StrictFPModifier     = 1 << 10
};

template<typename T>
T constant_value(const qint64* realval)
{
  T value;
  memcpy(&value, realval, sizeof(T));
  return value;
}

class TemplateParameterDeclaration;

class JavaType
{
  friend class TypeRepository;
  friend class TypeBuilder;

public:
  JavaType(TypeModifiers modifiers = NoModifier);

  TypeModifiers modifiers() const;

  void clear();

  bool equals(const JavaType* rhs) const;

  QString cvString() const;
  QString cvMangled() const;
  uint cvHash(uint input) const { return input; }

private:
  TypeModifiers m_mod;
};

class IntegralType : public KDevelop::IntegralType, public JavaType
{
  friend class TypeRepository;

public:
  typedef KSharedPtr<IntegralType> Ptr;

  enum IntegralTypes {
    TypeVoid,
    TypeNone,
    TypeNull,
    TypeChar,
    TypeBoolean,
    TypeByte,
    TypeShort,
    TypeInt,
    TypeLong,
    TypeFloat,
    TypeDouble
  };

  IntegralTypes integralType() const;

  virtual QString toString() const;

  virtual QString mangled() const;

  virtual uint hash() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;

protected:
  IntegralType(IntegralTypes type, TypeModifiers modifiers = NoModifier);

private:
  IntegralTypes m_type;
};

/**
 * An integral type that additionally has a constant value
 * */
class ConstantIntegralType : public IntegralType
{
  friend class TypeRepository;

public:
  typedef KSharedPtr<ConstantIntegralType> Ptr;

  /**The types and modifiers are not changed!
   * The values are casted internally to the local representation, so you can lose precision.
   * */
  template<class ValueType>
  void setValue(ValueType value) {
    if(integralType() == TypeFloat)
      setValueInternal<float>(value);
    else if(integralType() == TypeDouble)
      setValueInternal<double>(value);
    else
      setValueInternal<qint64>(value);
  }

  /**
   * For booleans, the value is 1 for true, and 0 for false.
   * All signed values should be retrieved and set through value(),
   *
   * */
  template<class ValueType>
  ValueType value() const {
    if(integralType() == TypeFloat)
      return constant_value<float>(&m_value);
    else if(integralType() == TypeDouble)
      return constant_value<double>(&m_value);
    else
      return constant_value<qint64>(&m_value);
  }

  virtual QString toString() const;

  virtual AbstractType* clone() const;

  virtual uint hash() const;

  ConstantIntegralType(IntegralTypes type, TypeModifiers modifiers = NoModifier);
private:
  //Sets the value without casting
  template<class ValueType>
  void setValueInternal(ValueType value);
  qint64 m_value;
};

class FunctionType : public KDevelop::FunctionType, public KDevelop::IdentifiedType, public JavaType
{
public:
  typedef KSharedPtr<FunctionType> Ptr;

  FunctionType(TypeModifiers modifiers = NoModifier);

  ///Declarations of this class(@see KDevelop::IdentifiedType::declaration()) are guaranteed to be based on AbstractFunctionDeclaration

  virtual QString toString() const;

  virtual uint hash() const;

  virtual QString mangled() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;
};

class PointerType : public KDevelop::PointerType, public JavaType
{
public:
  typedef KSharedPtr<PointerType> Ptr;

  PointerType(TypeModifiers modifiers = NoModifier);

  virtual QString toString() const;

  virtual QString mangled() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;

  virtual uint hash() const;
};

class ReferenceType : public KDevelop::ReferenceType, public JavaType
{
public:
  typedef KSharedPtr<ReferenceType> Ptr;

  ReferenceType(TypeModifiers modifiers = NoModifier);

  virtual QString toString() const;

  virtual QString mangled() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;

  virtual uint hash() const;
};

class ClassType : public KDevelop::StructureType, public KDevelop::IdentifiedType, public JavaType
{
public:
  typedef KSharedPtr<ClassType> Ptr;

  ClassType(TypeModifiers modifiers = NoModifier);

  const QList<ClassType::Ptr>& extendsClasses() const;
  void addExtendsClass(const ClassType::Ptr& baseClass);
  void clearExtendsClasses();

  const QList<ClassType::Ptr>& implementsInterfaces() const;
  void addImplementsInterface(const ClassType::Ptr& baseClass);
  void clearImplementsInterfaces();

  enum Type
  {
    Class,
    Interface
  };

  void setClassType(Type type);
  Type classType() const;

  /// Java classes are closed types, once they are defined, they can't be changed.
  bool isClosed() const { return m_closed; }
  void close() { m_closed = true; }

  ///After clearing, a class-type is open again.
  void clear();

  /// Error if the type is closed.
  virtual void addElement(KDevelop::AbstractType::Ptr element);

  virtual uint hash() const;

  virtual QString toString() const;

  virtual QString mangled() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;

  virtual void accept0 (KDevelop::TypeVisitor *v) const;

  virtual void exchangeTypes(KDevelop::TypeExchanger*);

private:
  QList<ClassType::Ptr> m_extendsClasses, m_implementsInterfaces;
  Type m_classType;
  bool m_closed;
};

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

  //TODO
  //virtual QString mangled() const;

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

  virtual QString mangled() const;

  virtual uint hash() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;

  virtual void accept0 (KDevelop::TypeVisitor *v) const;

private:
  ClassType::Ptr m_extendsType, m_superType;
};

class EnumeratorType : public ConstantIntegralType
{
public:
  typedef KSharedPtr<EnumeratorType> Ptr;

  EnumeratorType();
};

class EnumerationType : public IntegralType, public KDevelop::IdentifiedType
{
public:
  typedef KSharedPtr<EnumerationType> Ptr;

  EnumerationType(TypeModifiers modifiers = NoModifier);

  virtual uint hash() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;

  virtual QString mangled() const;

  virtual QString toString() const;
};

class ArrayType : public KDevelop::ArrayType
{
public:
  typedef KSharedPtr<ArrayType> Ptr;

  virtual QString mangled() const;

  virtual AbstractType* clone() const;

  virtual bool equals(const AbstractType* rhs) const;
};

}

#endif // CPPTYPES_H

