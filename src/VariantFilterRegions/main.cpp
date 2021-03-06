#include "Exceptions.h"
#include "ToolBase.h"
#include "ChromosomalIndex.h"
#include "VariantList.h"
#include "BedFile.h"
#include "Helper.h"
#include "VariantFilter.h"

class ConcreteTool
		: public ToolBase
{
	Q_OBJECT

public:
	ConcreteTool(int& argc, char *argv[])
		: ToolBase(argc, argv)
	{
	}

	virtual void setup()
	{
		setDescription("Filter a variant list based on a target region.");
		addInfile("in", "Input variant list.", false);
		addOutfile("out", "Output variant list. If unset, writes to STDOUT.", false);
		//optional
		addInfile("reg", "Input target region in BED format.", true);
		addString("r", "Single target region in the format chr17:41194312-41279500.", true);
		addFlag("invert", "If used, the variants inside the target region are removed.");

		changeLog(2016, 6, 10, "Added single target region parameter '-r'.");
	}

	virtual void main()
	{
		//load variants
		VariantList variants;
		variants.load(getInfile("in"));

		//init filter
		VariantFilter filter(variants);

		//filter by BED file
		QString reg = getInfile("reg");
		if (!reg.isEmpty())
		{
			BedFile regions;
			regions.load(reg);
			regions.merge();
			filter.flagByRegions(regions);
		}

		//filter by region string
		reg = getString("r");
		if (!reg.isEmpty())
		{
			filter.flagByRegion(BedLine::fromString(reg));
		}

		if (getFlag("invert")) filter.invert();

		filter.apply();

		variants.store(getOutfile("out"));
	}
};

#include "main.moc"

int main(int argc, char *argv[])
{
	ConcreteTool tool(argc, argv);
	return tool.execute();
}
