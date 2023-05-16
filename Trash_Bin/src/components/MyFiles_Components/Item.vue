<script lang="ts">
import { defineComponent } from 'vue';
import {Types} from '../../types'
import DeleteButton from '../General_Components/DeleteButton.vue'
    
function makeTable(content: string, delimiter: string) {
    //console.log(content)
    let rows = content.split('\n')
    let table: string[][] = []
    for (let row = 0; row < rows.length; row++) {
        //console.log(rows[row].trim())
        table.push(rows[row].trim().split(delimiter))
    }
    return table
}

    export default defineComponent ({
        props: {
            item: Types.Item
        },
        data() {return {
            display: [[""]],
            toggle: false,
            padding: (this.item != undefined) ? this.item.depth * 10 + "px" : "0px"
        }},
        components: {
            DeleteButton
        },
        emits: ['delete'],
        created() {
            if (this.item == undefined) {
                this.display = [['error']]
            }
            else if (this.item.extention.toLowerCase() == "csv") {
                this.display = makeTable(this.item?.content, ',')
            }
            else if (this.item.extention.toLowerCase() == "tsv") {
                this.display = makeTable(this.item?.content, '\t')
            }
            //console.log(this.display)
        }
    })
</script>

<template>
    <div :style="{'padding-left':padding}">
        <span @click="toggle = !toggle">
            📄Name: {{ item?.name }}, Extention: {{ item?.extention }}
        </span>
        <DeleteButton @click="$emit('delete')" />
    </div>
    <div v-if="toggle" v-for="row in display">
        <span v-for="item in row">{{ item }} {{'\t'}} </span>
    </div>
</template>

<style>

</style>