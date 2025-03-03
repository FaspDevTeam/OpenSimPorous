import { defineConfig } from "vitepress";
import markdownItKatex from "markdown-it-katex";
import markdownItFootnote from "markdown-it-footnote";
import { version } from "../../../package.json";

const customElements = [
  "math",
  "maction",
  "maligngroup",
  "malignmark",
  "menclose",
  "merror",
  "mfenced",
  "mfrac",
  "mi",
  "mlongdiv",
  "mmultiscripts",
  "mn",
  "mo",
  "mover",
  "mpadded",
  "mphantom",
  "mroot",
  "mrow",
  "ms",
  "mscarries",
  "mscarry",
  "mscarries",
  "msgroup",
  "mstack",
  "mlongdiv",
  "msline",
  "mstack",
  "mspace",
  "msqrt",
  "msrow",
  "mstack",
  "mstack",
  "mstyle",
  "msub",
  "msup",
  "msubsup",
  "mtable",
  "mtd",
  "mtext",
  "mtr",
  "munder",
  "munderover",
  "semantics",
  "math",
  "mi",
  "mn",
  "mo",
  "ms",
  "mspace",
  "mtext",
  "menclose",
  "merror",
  "mfenced",
  "mfrac",
  "mpadded",
  "mphantom",
  "mroot",
  "mrow",
  "msqrt",
  "mstyle",
  "mmultiscripts",
  "mover",
  "mprescripts",
  "msub",
  "msubsup",
  "msup",
  "munder",
  "munderover",
  "none",
  "maligngroup",
  "malignmark",
  "mtable",
  "mtd",
  "mtr",
  "mlongdiv",
  "mscarries",
  "mscarry",
  "msgroup",
  "msline",
  "msrow",
  "mstack",
  "maction",
  "semantics",
  "annotation",
  "annotation-xml",
];

export default defineConfig({
  title: "OpenCAEPoro",
  description: "The documentation for OpenCAEPoro",
  lastUpdated: true,
  ignoreDeadLinks: true,
  markdown: {
    headers: {
      level: [0, 0],
    },
    lineNumbers: true,
    config: (md) => {
      md.use(markdownItKatex), md.use(markdownItFootnote);
    },
  },
  vue: {
    template: {
      compilerOptions: {
        isCustomElement: (tag) => customElements.includes(tag),
      },
    },
  },
  themeConfig: {
    algolia: {
      appId: "6ID26UTF7C",
      apiKey: "8ac56d9d000db4351e0599a63f301056",
      indexName: "OpenCAEPoro",
    },
    outine: [2, 3],
    footer: {
      message: "This website is developed using vitepress.",
      copyright: "By the OpenCAEPlus project, 2022",
    },
    nav: [
      { text: "OpenCAE+", link: "https://opencaeplus.org" },
      { text: "Manual", link: "/manual/Design", activeMatch: "/manual/" },
      { text: "API", link: "/api/indexpage", activeMatch: "/api/" },
      {
        text: version,
        items: [
          {
            text: "Readme",
            link: "https://github.com/FaspDevTeam/OpenCAEPoro/blob/main/README.md",
          },
          {
            text: "Contribute",
            link: "https://github.com/FaspDevTeam/OpenCAEPoro/blob/main/CONTRIBUTE.md",
          },
        ],
      },
    ],
    socialLinks: [
      { icon: "github", link: "https://github.com/FaspDevTeam/OpenCAEPoro" },
    ],
    sidebar: {
      "/manual/": getManual(),
      "/api/": getAPI(),
    },
    editLink: {
      pattern:
        "https://github.com/FaspDevTeam/OpenCAEPoro/edit/main/doc/website/:path",
      text: "Edit this page on GitHub",
    },
  },
});

function getManual() {
  return [{
    text: "Manual",
    collapsible: false,
    items: [
        { text: "Design", link: "/manual/Design" },
        { text: "Keywords", link: "/manual/Keywords" },
    ]
  }
  ];
}

function getAPI() {
    const classList = ['AllWells',
    'BOMixture',
    'BOMixture_ODGW',
    'BOMixture_OW',
    'BOMixture_W',
    'BulkConn',
    'Bulk',
    'BulkPair',
    'COMP',
    'ConnGrid',
    'ControlNR',
    'ControlPreTime',
    'ControlTime',
    'COOIJK',
    'COORD',
    'CriticalInfo',
    'DetailInfo',
    'Dimens',
    'EoScontrol',
    'EoSparam',
    'FaspSolver',
    'FastControl',
    'FlowUnit',
    'FlowUnit_ODGW01',
    'FlowUnit_ODGW01_Miscible',
    'FlowUnit_ODGW02',
    'FlowUnit_ODGW',
    'FlowUnit_OG',
    'FlowUnit_OW',
    'FlowUnit_W',
    'FluidSolver',
    'GB_Pair',
    'GeneralConnect',
    'GetCycleNum',
    'GetWallTime',
    'GPair',
    'Grid',
    'HalfConn',
    'HexahedronFace',
    'Hexahedron',
    'LinearSolver',
    'LinearSystem',
    'Matrix3',
    'Miscstr',
    'MixtureComp',
    'Mixture',
    'NRparamSP',
    'NRparamSTA',
    'OCP_AIMc',
    'OCP_AIMs',
    'OCP_AIMt',
    'OCPControl',
    'OCP_FIM',
    'OCP_FIMn',
    'OCPIJK',
    'OCP_IMPEC',
    'OCPOutput',
    'OCPTable',
    'OCPType_Sum',
    'OpenCAEPoro',
    'OutputDetail',
    'OutputSummary',
    'ParamControl',
    'ParamEQUIL',
    'ParamOutput',
    'ParamRead',
    'ParamReservoir',
    'ParamWell',
    'Perforation',
    'Point2D',
    'Point3D',
    'Reservoir',
    'ResFIM',
    'Rock',
    'RRparam',
    'ScalarFaspSolver',
    'SolventINJ',
    'Solvent',
    'Solver',
    'SSMparamSP',
    'SSMparamSTA',
    'Summary',
    'SumPair',
    'TableSet',
    'TuningPair',
    'Type_A_o',
    'Type_A_r',
    'Type_B_o',
    'VectorFaspSolver',
    'WellGroup',
    'Well',
    'WellOpt',
    'WellOptPair',
    'WellOptParam',
    'WellParam']
    const fileList = ['classAllWells.md',
    'classBOMixture.md',
    'classBOMixture__ODGW.md',
    'classBOMixture__OW.md',
    'classBOMixture__W.md',
    'classBulkConn.md',
    'classBulk.md',
    'classBulkPair.md',
    'classCOMP.md',
    'classConnGrid.md',
    'classControlNR.md',
    'classControlPreTime.md',
    'classControlTime.md',
    'classCOOIJK.md',
    'classCOORD.md',
    'classCriticalInfo.md',
    'classDetailInfo.md',
    'classDimens.md',
    'classEoScontrol.md',
    'classEoSparam.md',
    'classFaspSolver.md',
    'classFastControl.md',
    'classFlowUnit.md',
    'classFlowUnit__ODGW01.md',
    'classFlowUnit__ODGW01__Miscible.md',
    'classFlowUnit__ODGW02.md',
    'classFlowUnit__ODGW.md',
    'classFlowUnit__OG.md',
    'classFlowUnit__OW.md',
    'classFlowUnit__W.md',
    'classFluidSolver.md',
    'classGB__Pair.md',
    'classGeneralConnect.md',
    'classGetCycleNum.md',
    'classGetWallTime.md',
    'classGPair.md',
    'classGrid.md',
    'classHalfConn.md',
    'classHexahedronFace.md',
    'classHexahedron.md',
    'classLinearSolver.md',
    'classLinearSystem.md',
    'classMatrix3.md',
    'classMiscstr.md',
    'classMixtureComp.md',
    'classMixture.md',
    'classNRparamSP.md',
    'classNRparamSTA.md',
    'classOCP__AIMc.md',
    'classOCP__AIMs.md',
    'classOCP__AIMt.md',
    'classOCPControl.md',
    'classOCP__FIM.md',
    'classOCP__FIMn.md',
    'classOCPIJK.md',
    'classOCP__IMPEC.md',
    'classOCPOutput.md',
    'classOCPTable.md',
    'classOCPType__Sum.md',
    'classOpenCAEPoro.md',
    'classOutputDetail.md',
    'classOutputSummary.md',
    'classParamControl.md',
    'classParamEQUIL.md',
    'classParamOutput.md',
    'classParamRead.md',
    'classParamReservoir.md',
    'classParamWell.md',
    'classPerforation.md',
    'classPoint2D.md',
    'classPoint3D.md',
    'classReservoir.md',
    'classResFIM.md',
    'classRock.md',
    'classRRparam.md',
    'classScalarFaspSolver.md',
    'classSolventINJ.md',
    'classSolvent.md',
    'classSolver.md',
    'classSSMparamSP.md',
    'classSSMparamSTA.md',
    'classSummary.md',
    'classSumPair.md',
    'classTableSet.md',
    'classTuningPair.md',
    'classType__A__o.md',
    'classType__A__r.md',
    'classType__B__o.md',
    'classVectorFaspSolver.md',
    'classWellGroup.md',
    'classWell.md',
    'classWellOpt.md',
    'classWellOptPair.md',
    'classWellOptParam.md',
    'classWellParam.md']

    let classItems=[];
    for (let index = 0; index < classList.length; index++) {
        classItems.push({text:classList[index],link:`/api/Classes/${fileList[index]}`});
    }

  return [
    {
      text: "Overview",
      collapsible: false,
      items: [
        { text: "Developer", link: "/api/developers" },
        { text: "Build", link: "/api/build" },
      ],
    },
    {
      text: "Classes",
      collapsible: true,
      items: [
        ...classItems,
    ],
    }
  ];
}
