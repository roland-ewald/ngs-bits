#include "TestFramework.h"

TEST_CLASS(FastqToFasta_Test)
{
Q_OBJECT
private slots:
	
	void base_test()
	{
		EXECUTE("FastqToFasta", "-in " + TESTDATA("data_in/FastqToFasta_in1.fastq.gz") + " -out out/FastqToFasta_out1.fasta");
		COMPARE_GZ_FILES("out/FastqToFasta_out1.fasta", TESTDATA("data_out/FastqToFasta_out1.fasta"));
	}

};
