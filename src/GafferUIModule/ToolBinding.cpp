//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2014, John Haddon. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#include "boost/python.hpp"

#include "ToolBinding.h"

#include "GafferUI/Tool.h"
#include "GafferUI/View.h"

#include "GafferBindings/NodeBinding.h"

using namespace std;
using namespace boost::python;
using namespace IECorePython;
using namespace GafferUI;

static boost::python::list registeredTools( IECore::TypeId viewType )
{
	vector<string> tools;
	Tool::registeredTools( viewType, tools );
	boost::python::list result;
	for( vector<string>::const_iterator it = tools.begin(), eIt = tools.end(); it!=eIt; ++it )
	{
		result.append( *it );
	}
	return result;
}

void GafferUIModule::bindTool()
{
	GafferBindings::NodeClass<Tool>( nullptr, no_init )
		.def( "view", (View *(Tool::*)())&Tool::view, return_value_policy<CastToIntrusivePtr>() )
		.def( "create", &Tool::create )
		.staticmethod( "create" )
		.def( "registeredTools", &registeredTools )
		.staticmethod( "registeredTools" )
	;
}
