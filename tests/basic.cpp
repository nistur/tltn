#include "tltn-tests.h"
#include "tltn.h"

TEST(InitTerminate, Basic, 0.0f,
     // initialisation
     {
	 m_data.context = 0;
     },
     // cleanup
     {
	 tltnTerminateContext(&m_data.context);
     },
     // test
     {
	 ASSERT(tltnInitContext(&m_data.context, 23) == TLTN_SUCCESS);
      ASSERT(m_data.context != 0);
	 ASSERT(tltnTerminateContext(&m_data.context) == TLTN_SUCCESS);
      ASSERT(m_data.context == 0)
     },
     // data
     {
	 tltnContext* context;
     }
    );
