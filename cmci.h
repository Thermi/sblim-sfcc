
/*
 * cmpic.h
 *
 * (C) Copyright IBM Corp. 2005
 *
 * THIS FILE IS PROVIDED UNDER THE TERMS OF THE COMMON PUBLIC LICENSE
 * ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
 * CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
 *
 * You can obtain a current copy of the Common Public License from
 * http://oss.software.ibm.com/developerworks/opensource/license-cpl.html
 *
 * Author:        Adrian Schuur <schuur@de.ibm.com>
 *
 * Description:
 *
 * CMPI Client function tables.
 *
*/

#ifndef _CMPIC_H_
#define _CMPIC_H_

#include "cmcidt.h"
#include "cmcift.h"
#include "cmcimacs.h"
#include "utilList.h"

#ifdef __cplusplus
extern "C" {
#endif



   //---------------------------------------------------
   //--
   //	_CMCIClientFt Function Table
   //--
   //---------------------------------------------------


   /** This structure is a table of pointers to client CIMOM services.
   */
#define native_new_CMPIObjectPath   newCMPIObjectPath

CMPIObjectPath * newCMPIObjectPath ( const char * namespace, 
					     const char * classname,
					     CMPIStatus * rc );

struct _CMCIClient;
typedef struct _CMCIClient CMCIClient;
   
struct _CMCIConnection;
typedef struct _CMCIConnection CMCIConnection;
   
struct _ClientEnc;
typedef struct _ClientEnc ClientEnc;
   
typedef struct _CMCIClientFT {
   
      /** Enumerate Instance Names of the class (and subclasses) defined by &lt;op&gt;.
	 @param cl Client this pointer.
	 @param op ObjectPath containing namespace and classname components.
	 @param rc Output: Service return status (suppressed when NULL).
	 @return Enumeration of ObjectPathes.
     */
     CMPIEnumeration* (*enumInstanceNames)
                (CMCIClient* cl,
                 CMPIObjectPath* op, CMPIStatus* rc);

      /** Get Instance using &lt;op&gt; as reference. Instance structure can be
         controled using the CMPIInvocationFlags entry in &lt;ctx&gt;.
	 @param cl Client this pointer.
	 @param op ObjectPath containing namespace, classname and key components.
	 @param properties If not NULL, the members of the array define one or more Property
	     names. Each returned Object MUST NOT include elements for any Properties
	     missing from this list
	 @param rc Output: Service return status (suppressed when NULL).
	 @return The Instance.
     */
     CMPIInstance* (*getInstance)
                (CMCIClient* cl,
                 CMPIObjectPath* op, char** properties, CMPIStatus* rc);

     // class 2 services

      /** Create Instance from &lt;inst&gt; using &lt;op&gt; as reference.
	 @param cl Client this pointer.
	 @param op ObjectPath containing namespace, classname and key components.
	 @param inst Complete instance.
	 @param rc Output: Service return status (suppressed when NULL).
	 @return The assigned instance reference.
     */
     CMPIObjectPath* (*createInstance)
                (CMCIClient* cl,
                 CMPIObjectPath* op, CMPIInstance* inst, CMPIStatus* rc);

      /** Replace an existing Instance from &lt;inst&gt; using &lt;op&gt; as reference.
	 @param cl Client this pointer.
	 @param op ObjectPath containing namespace, classname and key components.
	 @param inst Complete instance.
	 @return Service return status.
     */
     CMPIStatus (*setInstance)
                (CMCIClient* cl,
                 CMPIObjectPath* op, CMPIInstance* inst, char ** properties);

      /** Delete an existing Instance using &lt;op&gt; as reference.
	 @param cl Client this pointer.
	 @param op ObjectPath containing namespace, classname and key components.
	 @return Service return status.
     */
     CMPIStatus (*deleteInstance)
                (CMCIClient* cl,
                 CMPIObjectPath* op);

      /** Query the enumeration of instances of the class (and subclasses) defined
         by &lt;op&gt; using &lt;query&gt; expression.
	 @param cl Client this pointer.
	 @param op ObjectPath containing namespace and classname components.
	 @param query Query expression
	 @param lang Query Language
	 @param rc Output: Service return status (suppressed when NULL).
	 @return Resulting eumeration of Instances.
     */
     CMPIEnumeration* (*execQuery)
                (CMCIClient* cl,
                 CMPIObjectPath* op, const char *query, const char *lang, CMPIStatus* rc);

      /** Enumerate Instances of the class (and subclasses) defined by &lt;op&gt;.
         Instance structure and inheritance scope can be controled using the
	 CMPIInvocationFlags entry in &lt;ctx&gt;.
	 @param cl Client this pointer.
	 @param op ObjectPath containing namespace and classname components.
	 @param properties If not NULL, the members of the array define one or more Property
	     names. Each returned Object MUST NOT include elements for any Properties
	     missing from this list
	 @param rc Output: Service return status (suppressed when NULL).
	 @return Enumeration of Instances.
     */
     CMPIEnumeration* (*enumInstances)
                (CMCIClient* cl,
                 CMPIObjectPath* op, char** properties, CMPIStatus* rc);

      /** Enumerate instances associated with the Instance defined by the &lt;op&gt;.
	 @param cl Client this pointer.
	 @param op Source ObjectPath containing namespace, classname and key components.
	 @param assocClass If not NULL, MUST be a valid Association Class name.
	    It acts as a filter on the returned set of Objects by mandating that
	    each returned Object MUST be associated to the source Object via an
	    Instance of this Class or one of its subclasses.
	 @param resultClass If not NULL, MUST be a valid Class name.
	    It acts as a filter on the returned set of Objects by mandating that
	    each returned Object MUST be either an Instance of this Class (or one
	    of its subclasses).
	 @param role If not NULL, MUST be a valid Property name.
	    It acts as a filter on the returned set of Objects by mandating
	    that each returned Object MUST be associated to the source Object
	    via an Association in which the source Object plays the specified role
	    (i.e. the name of the Property in the Association Class that refers
	    to the source Object MUST match the value of this parameter).
	 @param resultRole If not NULL, MUST be a valid Property name.
	    It acts as a filter on the returned set of Objects by mandating
	    that each returned Object MUST be associated to the source Object
	    via an Association in which the returned Object plays the specified role
	    (i.e. the name of the Property in the Association Class that refers to
	    the returned Object MUST match the value of this parameter).
	 @param properties If not NULL, the members of the array define one or more Property
	     names. Each returned Object MUST NOT include elements for any Properties
	     missing from this list
	 @param rc Output: Service return status (suppressed when NULL).
	 @return Enumeration of Instances.
     */
     CMPIEnumeration* (*associators)
                (CMCIClient* cl,
                 CMPIObjectPath* op, const char *assocClass, const char *resultClass,
		 const char *role, const char *resultRole, char** properties, CMPIStatus* rc);

      /** Enumerate ObjectPaths associated with the Instance defined by &lt;op&gt;.
	 @param cl Client this pointer.
	 @param op Source ObjectPath containing namespace, classname and key components.
	 @param assocClass If not NULL, MUST be a valid Association Class name.
	    It acts as a filter on the returned set of Objects by mandating that
	    each returned Object MUST be associated to the source Object via an
	    Instance of this Class or one of its subclasses.
	 @param resultClass If not NULL, MUST be a valid Class name.
	    It acts as a filter on the returned set of Objects by mandating that
	    each returned Object MUST be either an Instance of this Class (or one
	    of its subclasses).
	 @param role If not NULL, MUST be a valid Property name.
	    It acts as a filter on the returned set of Objects by mandating
	    that each returned Object MUST be associated to the source Object
	    via an Association in which the source Object plays the specified role
	    (i.e. the name of the Property in the Association Class that refers
	    to the source Object MUST match the value of this parameter).
	 @param resultRole If not NULL, MUST be a valid Property name.
	    It acts as a filter on the returned set of Objects by mandating
	    that each returned Object MUST be associated to the source Object
	    via an Association in which the returned Object plays the specified role
	    (i.e. the name of the Property in the Association Class that refers to
	    the returned Object MUST match the value of this parameter).
	 @param rc Output: Service return status (suppressed when NULL).
	 @return Enumeration of ObjectPaths.
     */
     CMPIEnumeration* (*associatorNames)
                (CMCIClient* cl,
                 CMPIObjectPath* op, const char *assocClass, const char *resultClass,
		 const char *role, const char *resultRole, CMPIStatus* rc);

       /** Enumerates the association instances that refer to the instance defined by
           &lt;op&gt;.
	 @param cl Client this pointer.
	 @param op Source ObjectPath containing namespace, classname and key components.
	 @param resultClass If not NULL, MUST be a valid Class name.
	    It acts as a filter on the returned set of Objects by mandating that
	    each returned Object MUST be either an Instance of this Class (or one
	    of its subclasses).
	 @param role If not NULL, MUST be a valid Property name.
	    It acts as a filter on the returned set of Objects by mandating
	    that each returned Object MUST be associated to the source Object
	    via an Association in which the source Object plays the specified role
	    (i.e. the name of the Property in the Association Class that refers
	    to the source Object MUST match the value of this parameter).
	 @param properties If not NULL, the members of the array define one or more Property
	     names. Each returned Object MUST NOT include elements for any Properties
	     missing from this list
	 @param rc Output: Service return status (suppressed when NULL).
	 @return Enumeration of ObjectPaths.
     */
     CMPIEnumeration* (*references)
                (CMCIClient* cl,
                 CMPIObjectPath* op, const char *resultClass ,const char *role ,
		 char** properties, CMPIStatus* rc);

       /** Enumerates the association ObjectPaths that refer to the instance defined by
           &lt;op&gt;.
	 @param cl Client this pointer.
	 @param op Source ObjectPath containing namespace, classname and key components.
	 @param resultClass If not NULL, MUST be a valid Class name.
	    It acts as a filter on the returned set of Objects by mandating that
	    each returned Object MUST be either an Instance of this Class (or one
	    of its subclasses).
	 @param role If not NULL, MUST be a valid Property name.
	    It acts as a filter on the returned set of Objects by mandating
	    that each returned Object MUST be associated to the source Object
	    via an Association in which the source Object plays the specified role
	    (i.e. the name of the Property in the Association Class that refers
	    to the source Object MUST match the value of this parameter).
	 @param rc Output: Service return status (suppressed when NULL).
	 @return Enumeration of ObjectPaths.
       */
     CMPIEnumeration* (*referenceNames)
                (CMCIClient* cl,
                 CMPIObjectPath* op, const char *resultClass ,const char *role,
                 CMPIStatus* rc);

       /** Invoke a named, extrinsic method of an Instance
         defined by the &lt;op&gt; parameter.
	 @param cl Client this pointer.
	 @param op ObjectPath containing namespace, classname and key components.
	 @param method Method name
	 @param in Input parameters.
	 @param out Output parameters.
	 @param rc Output: Service return status (suppressed when NULL).
	 @return Method return value.
      */
     CMPIData (*invokeMethod)
                (CMCIClient* cl,
                 CMPIObjectPath* op,const char *method,
		 CMPIArgs* in, CMPIArgs* out, CMPIStatus* rc);

       /** Set the named property value of an Instance defined by the &lt;op&gt; parameter.
	 @param cl Client this pointer.
	 @param op ObjectPath containing namespace, classname and key components.
	 @param name Property name
	 @param value Value.
	 @param type Value type.
	 @return Service return status.
      */
     CMPIStatus (*setProperty)
                (CMCIClient* cl,
                 CMPIObjectPath* op, const char *name , CMPIValue* value,
                 CMPIType type);

       /** Get the named property value of an Instance defined by the &lt;op&gt; parameter.
	 @param cl Client this pointer.
	 @param op ObjectPath containing namespace, classname and key components.
	 @param name Property name
	 @param rc Output: Service return status (suppressed when NULL).
	 @return Property value.
      */
     CMPIData (*getProperty)
                (CMCIClient *cl, 
                 CMPIObjectPath *op, const char *name, CMPIStatus *rc);

} CMCIClientFT;

typedef struct clientData {
   char *hostName;
   char *port;
   char *user;
   char *pwd;
   char *scheme;
   int  status;
} CMCIClientData;

struct _CMCIClient {
   void *hdl;
   CMCIClientFT *ft;
};   

CMCIClient *cmciConnect(const char *hn, const char *port, 
                        const char *user, const char *pwd, CMPIStatus *rc);   
   
#ifdef __cplusplus
 };
#endif

#endif // _CMPIC_H_
