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

#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/abstractfunctiondeclaration.h>
#include <language/duchain/forwarddeclarationtype.h>

using namespace KDevelop;
namespace java {

//Because all these classes have no d-pointers, shallow copies are perfectly fine

AbstractType* FunctionType::clone() const {
  return new FunctionType(*this);
}

AbstractType* ConstantIntegralType::clone() const {
  return new ConstantIntegralType(*this);
}

AbstractType* PointerType::clone() const {
  return new PointerType(*this);
}

AbstractType* ReferenceType::clone() const {
  return new ReferenceType(*this);
}

AbstractType* ClassType::clone() const {
  return new ClassType(*this);
}

AbstractType* EnumerationType::clone() const {
  return new EnumerationType(*this);
}

AbstractType* ArrayType::clone() const {
  return new ArrayType(*this);
}

AbstractType* IntegralType::clone() const {
  return new IntegralType(*this);
}

bool JavaType::equals(const JavaType* rhs) const {
  return m_mod == rhs->m_mod;
}

bool FunctionType::equals(const AbstractType* _rhs) const
{
  if( !fastCast<const FunctionType*>(_rhs))
    return false;
  const FunctionType* rhs = static_cast<const FunctionType*>(_rhs);

  if( this == rhs )
    return true;

  //Ignore IdentifiedType here, because we do not want to respect that while comparing function-types.

  return JavaType::equals(rhs) && FunctionType::equals(rhs);
}

bool PointerType::equals(const AbstractType* _rhs) const
{
  if( !fastCast<const PointerType*>(_rhs))
    return false;
  const PointerType* rhs = static_cast<const PointerType*>(_rhs);

  if( this == rhs )
    return true;

  return JavaType::equals(rhs) && PointerType::equals(rhs);
}

bool ReferenceType::equals(const AbstractType* _rhs) const
{
  if( !fastCast<const ReferenceType*>(_rhs))
    return false;
  const ReferenceType* rhs = static_cast<const ReferenceType*>(_rhs);

  if( this == rhs )
    return true;

  return JavaType::equals(rhs) && ReferenceType::equals(rhs);
}

bool ClassType::equals(const AbstractType* _rhs) const
{
  if( !fastCast<const ClassType*>(_rhs) && !fastCast<const ForwardDeclarationType*>(_rhs))
    return false;
  const IdentifiedType* rhs = fastCast<const IdentifiedType*>(_rhs);

  Declaration* decl = declaration();
  Declaration* rhsDecl = rhs->declaration();

  if(!decl || !rhsDecl)
    return false;

  ///We cannot use here IdentifiedType::equals, because else we get problems with forward declarations
  return decl->equalQualifiedIdentifier(rhsDecl);
}

QString EnumerationType::mangled() const
{
  return QString("E_%1_%2").arg(IntegralType::mangled()).arg(identifier().toString());
}

bool EnumerationType::equals(const AbstractType* _rhs) const
{
  if( !fastCast<const EnumerationType*>(_rhs) && !fastCast<const ForwardDeclarationType*>(_rhs))
    return false;
  const IdentifiedType* rhs = fastCast<const IdentifiedType*>(_rhs);

  if( this == rhs )
    return true;

  return IdentifiedType::equals(rhs);
}

bool ArrayType::equals(const AbstractType* _rhs) const
{
  if( !fastCast<const ArrayType*>(_rhs))
    return false;
  const ArrayType* rhs = static_cast<const ArrayType*>(_rhs);

  if( this == rhs )
    return true;

  return ArrayType::equals(rhs);
}

bool IntegralType::equals(const AbstractType* _rhs) const
{
  if( !fastCast<const IntegralType*>(_rhs))
    return false;
  const IntegralType* rhs = static_cast<const IntegralType*>(_rhs);

  if( this == rhs )
    return true;

  return m_type == rhs->m_type && IntegralType::equals(rhs) && JavaType::equals(rhs);
}

void ClassType::accept0 (TypeVisitor *v) const
{
  if (v->visit (this))
    {
      foreach(const ClassType::Ptr& base, m_extendsClasses)
        acceptType (AbstractType::Ptr::staticCast(base), v);
      foreach(const ClassType::Ptr& base, m_implementsInterfaces)
        acceptType (AbstractType::Ptr::staticCast(base), v);
    }

  v->endVisit (this);
}

void ClassType::exchangeTypes(TypeExchanger *e)
{
  // TODO understand better...
  foreach (ClassType::Ptr base, m_extendsClasses)
    base = ClassType::Ptr::dynamicCast(AbstractType::Ptr(e->exchange(base.data())));
  foreach (ClassType::Ptr base, m_implementsInterfaces)
    base = ClassType::Ptr::dynamicCast(AbstractType::Ptr(e->exchange(base.data())));
}


// ---------------------------------------------------------------------------
const QList<ClassType::Ptr>& ClassType::extendsClasses() const
{
  return m_extendsClasses;
}

void ClassType::addExtendsClass(const ClassType::Ptr& extendsClass)
{
  m_extendsClasses.append(extendsClass);
}

void ClassType::clearExtendsClasses()
{
  m_extendsClasses.clear();
}

void ClassType::setClassType(Type type)
{
  m_classType = type;
}

ClassType::Type ClassType::classType() const
{
  return m_classType;
}

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
EnumeratorType::EnumeratorType() : ConstantIntegralType(TypeInt)
{
}

ClassType::ClassType(TypeModifiers modifiers)
  : JavaType(modifiers)
  , m_classType(Class)
  , m_closed(false)
{
}


ConstantIntegralType::ConstantIntegralType(IntegralTypes type, TypeModifiers modifiers) : IntegralType(type, modifiers) {
}

template<>
void ConstantIntegralType::setValueInternal<qint64>(qint64 value) {
  m_value = value;
}

template<>
void ConstantIntegralType::setValueInternal<quint64>(quint64 value) {
  m_value = (qint64)value;
}

template<>
void ConstantIntegralType::setValueInternal<float>(float value) {
  if(integralType() != TypeFloat)
    kWarning() << "setValue(float) called on non-float type";
  memcpy(&m_value, &value, sizeof(float));
}

template<>
void ConstantIntegralType::setValueInternal<double>(double value) {
  if(integralType() != TypeDouble)
    kWarning() << "setValue(double) called on non-double type";
  memcpy(&m_value, &value, sizeof(double));
}

uint ConstantIntegralType::hash() const {
  uint ret = IntegralType::hash();
  ret += 47 * (uint)m_value + 11*(uint)integralType();
  return ret;
}

QString ConstantIntegralType::toString() const {
  switch(integralType()) {
    case TypeNone:
      return "none";
    case TypeChar:
      // TODO check correctness of the byte case
    case TypeByte:
      return QString("%1").arg((char)m_value);
    case TypeBoolean:
      return m_value ? "true" : "false";
    case TypeShort:
    case TypeInt:
    case TypeLong:
      return QString::number(m_value);
    case TypeFloat:
      return QString("%1").arg( value<float>() );
    case TypeDouble:
      return QString("%1").arg( value<double>() );
    case TypeVoid:
      return "void";
    case TypeNull:
      return "null";
  }
  return "<unknown_value>";
}

IntegralType::IntegralType(IntegralTypes type, TypeModifiers modifiers)
  : JavaType(modifiers)
  , m_type(type)
{
  QString name;

  switch (type) {
    case TypeChar:
      name = "char";
      break;
    case TypeByte:
      name = "byte";
      break;
    case TypeBoolean:
      name = "boolean";
      break;
    case TypeInt:
      name = "int";
      break;
    case TypeFloat:
      name = "float";
      break;
    case TypeDouble:
      name = "double";
      break;
    case TypeVoid:
      name = "void";
      break;
    default:
      name = "<notype>";
      break;
  }

  setName(name);
}

IntegralType::IntegralTypes IntegralType::integralType() const
{
  return m_type;
}

QString IntegralType::toString() const
{
  return KDevelop::IntegralType::toString();
}

void JavaType::clear() {
  m_mod = NoModifier;
}


JavaType::JavaType(TypeModifiers modifiers)
  : m_mod(modifiers)
{
}

QString FunctionType::toString() const
{
  return QString("%1 %2").arg(KDevelop::FunctionType::toString()).arg(cvString());
}

PointerType::PointerType(TypeModifiers modifiers)
  : JavaType(modifiers)
{
}

QString PointerType::toString() const
{
  return QString("%1%2").arg(KDevelop::PointerType::toString()).arg(cvString());
}

ReferenceType::ReferenceType(TypeModifiers modifiers)
  : JavaType(modifiers)
{
}

QString ReferenceType::toString() const
{
  return QString("%1%2").arg(KDevelop::ReferenceType::toString()).arg(cvString());
}

uint IntegralType::hash() const
{
  return cvHash(KDevelop::IntegralType::hash());
}

uint PointerType::hash() const
{
  return cvHash(KDevelop::PointerType::hash());
}

uint ReferenceType::hash() const
{
  return cvHash(KDevelop::ReferenceType::hash());
}

uint FunctionType::hash() const
{
  return cvHash(KDevelop::FunctionType::hash()) + 31 * identifier().hash();
}

uint ClassType::hash() const
{
  return identifier().hash();
}

void ClassType::addElement(AbstractType::Ptr element)
{
  if (isClosed())
    kWarning() << "Tried to add type" << element->toString() << "to closed class!" ;
  else
    StructureType::addElement(element);
}

void ClassType::clear() {
  StructureType::clear();
  IdentifiedType::clear();
  JavaType::clear();
  m_extendsClasses.clear();
  m_implementsInterfaces.clear();
  m_classType = Class;
  m_closed = false;
}

QString ClassType::toString() const
{
  QualifiedIdentifier id = identifier();
  if (!id.isEmpty())
    return id.top().toString();

  QString type;
  switch (classType()) {
    case Class:
      type = "class";
      break;
    case Interface:
      type = "interface";
      break;
  }
  return QString("<%1>%2").arg(type).arg(cvString());
}

EnumerationType::EnumerationType(TypeModifiers modifiers)
  : IntegralType(TypeInt, modifiers)
{
}

QString EnumerationType::toString() const
{
  return "enum " + identifier().toString();
}
uint EnumerationType::hash() const
{
  return identifier().hash();
}

QString IntegralType::mangled() const
{
  QString ret;

  switch (integralType()) {
    case TypeChar:
      ret += 'c';
      break;
    case TypeBoolean:
      ret += 'b';
      break;
    case TypeShort:
      ret += 's';
      break;
    case TypeLong:
      ret += 'l';
      break;
    case TypeInt:
      ret += 'i';
      break;
    case TypeFloat:
      ret += 'f';
      break;
    case TypeDouble:
      ret += 'd';
      break;
    case TypeVoid:
      ret += 'v';
      break;
    default:
      ret += '?';
      break;
  }
  return ret;// + cvMangled();
}

QString JavaType::cvMangled() const
{
  QString ret;
  // TODO mangle me
  return ret;
}

QString PointerType::mangled() const
{
  QString ret = "P" + cvMangled();
  if (baseType())
    ret += baseType()->mangled();
  return ret;
}

QString ReferenceType::mangled() const
{
  QString ret = "R" + cvMangled();
  if (baseType())
    ret += baseType()->mangled();
  return ret;
}

QString ClassType::mangled() const
{
  return idMangled() + cvMangled();
}

QString FunctionType::mangled() const
{
  ClassFunctionDeclaration* classFunctionDecl = dynamic_cast<ClassFunctionDeclaration*>(declaration());

  bool constructor = classFunctionDecl && classFunctionDecl->isConstructor();

  QualifiedIdentifier id = identifier();

  Identifier function = id.top();
  if (!id.isEmpty())
    id.pop();

  QString ret = QString("%1__%2%3").arg(constructor ? QString() : function.mangled()).arg(cvMangled()).arg(id.mangled());

  foreach (const AbstractType::Ptr& argument, arguments())
    if (argument)
      ret += argument->mangled();
    else
      ret += '?';

  return ret;
}

QString ArrayType::mangled() const
{
  return QString("A%1%2").arg(dimension()).arg(elementType() ? elementType()->mangled() : QString());
}

TypeModifiers JavaType::modifiers() const
{
  return m_mod;
}

ParameterizedType::ParameterizedType(TypeModifiers modifiers)
  : ClassType(modifiers)
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

}

QString java::JavaType::cvString() const
{
  // TODO
  return QString();
}

java::FunctionType::FunctionType(TypeModifiers modifiers)
  : JavaType(modifiers)
{
}

QString java::WildcardType::mangled() const
{
  return toString();
}

uint java::WildcardType::hash() const
{
  uint ret = 1;
  if (m_extendsType)
    ret += m_extendsType->hash() * 3;

  if (m_superType)
    ret += m_superType->hash() * 3;

  return ret;
}

bool java::WildcardType::equals(const AbstractType * rhs) const
{
  if (const WildcardType* wild = dynamic_cast<const WildcardType*>(rhs))
    if (wild->extendsType() == m_extendsType && wild->superType() == m_superType)
      return true;

  return false;
}

AbstractType * java::WildcardType::clone() const
{
  return new WildcardType(*this);
}

void java::WildcardType::accept0(TypeVisitor * v) const
{
  v->visit(this);
}

const QList< java::ClassType::Ptr > & java::ClassType::implementsInterfaces() const
{
  return m_implementsInterfaces;
}

void java::ClassType::addImplementsInterface(const ClassType::Ptr & interface)
{
  Q_ASSERT(interface->classType() == Interface);
  m_implementsInterfaces.append(interface);
}

void java::ClassType::clearImplementsInterfaces()
{
  m_implementsInterfaces.clear();
}
